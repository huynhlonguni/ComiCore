#pragma once

#include "path.h"
#include "panel.h"
#include "bound.h"
#include "raylib.h"
#include "raymath.h"
#include "illust.h"

#include <vector>
#include <iostream>
using namespace std;

class Page {
private:
	vector<Panel> panels;
	vector<Illust*> illusts;
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

	void draw() {
		DrawRectangle(0, 0, width, height, WHITE);

		vector<char> drawFlags(illusts.size(), 0);

		for (int i = 0; i < panels.size(); i++) {
			panels[i].draw();
			for (int j = 0; j < illusts.size(); j++) {
				if (illusts[j]->getParentPanel() == i) {
					drawFlags[j] = true;
					illusts[j]->draw();
				}
			}
		}

		for (int k = 0; k < illusts.size(); k++) {
			if (!drawFlags[k]) illusts[k]->draw();
		}
	}

	void slice(Paths sliceLines) {
		vector<Panel> res;

		for (Panel &panel : panels) {
			Paths solution = Clipper::Difference(panel.getPaths(), sliceLines, Clipper::FillRule::NonZero);
			Paths panelPaths;
			for (const Path &p : solution) {
				if (Clipper::IsPositive(p)) {
					if (panelPaths.size()) {
						res.push_back(panelPaths); //flush previous panel
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
			}
		}

		panels = res;
	}

	void addIllust(Image img) {
		illusts.push_back(new Illust(img));
	}

	vector<Illust*> getIllusts() {
		return illusts;
	}

	~Page() {
		for (int i = 0; i < illusts.size(); i++)
			delete illusts[i];
	}
};