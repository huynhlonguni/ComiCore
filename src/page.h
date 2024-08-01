#pragma once

#include "path.h"
#include "panel.h"
#include "bound.h"
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "attachments/attachment.h"
#include "attachments/illust.h"
#include "attachments/bubble.h"
#include "attachments/text.h"

#include <vector>
#include <iostream>
using namespace std;

class Page {
private:
	vector<Panel> panels;
	vector<Attachment*> attachments;
	int width = 0;
	int height = 0;

	Paths getDefaultPanelPaths(int width, int height, int paddingX = 20, int paddingY = 20) {
		Paths points(1, Path(4));
		//Counter clockwise
		points[0][0] = {paddingX, paddingY};
		points[0][1] = {paddingX, height - paddingY};
		points[0][2] = {width - paddingX, height - paddingY};
		points[0][3] = {width - paddingX, paddingY};

		return points;
	}

public:
	Page() {}
	Page(int width, int height) : width(width), height(height) {
		panels.push_back(getDefaultPanelPaths(width, height));
	}

	vector<Panel>& getPanels() {
		return panels;
	}

	void update() {
	}

	void draw(TextEngine *textEngine) {
		DrawRectangle(0, 0, width, height, WHITE);
		
		vector<char> drawFlags(attachments.size(), 0);

		for (int i = 0; i < panels.size(); i++) {
			rlDrawRenderBatchActive();
			rlEnableStencilTest();
			bool doDraw = false;

			//Draw stencil mask
			rlStencilFunc(RL_ALWAYS, 1, 0xFF);
			rlStencilOp(RL_REPLACE, RL_REPLACE, RL_REPLACE);

			rlColorMask(0,0,0,0);
			panels[i].drawMask();

			rlDrawRenderBatchActive(); //flush
			rlColorMask(1,1,1,1);

			//Test stencil
			rlStencilFunc(RL_EQUAL, 1, 0xFF);
			rlStencilOp(RL_KEEP, RL_KEEP, RL_KEEP);
			for (int j = 0; j < attachments.size(); j++) {
				if (attachments[j]->getParentPanel() == i) {
					drawFlags[j] = true;
					doDraw = true;
					attachments[j]->draw(textEngine);
				}
			}

			if (doDraw) rlDrawRenderBatchActive();

			rlDisableStencilTest();
			rlClearStencilBuffer();

			panels[i].draw();

		}

		for (int k = 0; k < attachments.size(); k++) {
			if (!drawFlags[k]) attachments[k]->draw(textEngine);
		}
	}

	void slice(Paths sliceLines) {
		vector<Panel> res;

		vector<vector<Attachment*>> panelAttachments(panels.size());

		for (int i = 0; i < panels.size(); i++) {
			for (int j = 0; j < attachments.size(); j++) {
				if (attachments[j]->getParentPanel() == i)
					panelAttachments[i].push_back(attachments[j]);
			}
		}

		for (int i = 0; i < panels.size(); i++) {
			Paths solution = Clipper::Difference(panels[i].getPaths(), sliceLines, Clipper::FillRule::NonZero);
			Paths panelPaths;
			int count = 0;
			for (const Path &p : solution) {
				if (Clipper::IsPositive(p)) {
					if (panelPaths.size()) {
						res.push_back(panelPaths); //flush previous panel
						count++;
					}
					panelPaths.clear();
					panelPaths.push_back({p});
				}
				else {
					panelPaths.push_back({p}); //push hole to unflushed panel
				}
			}
			if (panelPaths.size()) { //flush all
				res.push_back(panelPaths);
				count++;
			}

			for (int k = 0; k < panelAttachments[i].size(); k++) {
				double prevArea = 0;
				for (int j = res.size() - count; j < res.size(); j++) {
					double area = 0;
					Bound attachmentBound = panelAttachments[i][k]->getBound();
					Rect attachmentRect = Bound::getRectFromBound(attachmentBound);
					Paths sol = Clipper::RectClip(attachmentRect, res[j].getPaths());
					for (const Path &p: sol)
						area += Clipper::Area(p);

					if (area >= prevArea) {
						prevArea = area;
						panelAttachments[i][k]->setParentPanel(j);
					}
				}
			}
		}

		panels = res;
	}

	void addIllust(Image img) {
		attachments.push_back(new Illust(img));
	}

	void addBubble(Bubble bubble) {
		attachments.push_back(new Bubble(bubble));
	}

	void addText(Text text) {
		attachments.push_back(new Text(text));
	}

	int getAttachmentCount() {
		return attachments.size();
	}

	int getPanelCount() {
		return panels.size();
	}

	int getAttachmentPanel(int id) {
		if (id >= 0 && id < attachments.size())
			return attachments[id]->getParentPanel();
		return -1;
	}

	int getAttachmentType(int id) {
		if (id >= 0 && id < attachments.size())
			return attachments[id]->getType();
		return -1;
	}

	void setAttachmentPanel(int id, int panel) {
		if (id >= 0 && id < attachments.size())
			return attachments[id]->setParentPanel(panel);
	}

	vector<Attachment*> getAttachments() {
		return attachments;
	}

	~Page() {
		for (int i = 0; i < attachments.size(); i++)
			delete attachments[i];
	}
};