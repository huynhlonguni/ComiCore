#pragma once

#include "tool.h"
#include "../path.h"
#include "raylib.h"

#include <math.h>
#include <iostream>
using namespace std;

class TransformTool : public Tool {
private:
	int controlSize = 10;
	int controlOutline = 2;

	Point previousMouse;
	Attachment *workAttachment = NULL;
	float workRatio = 1.0;
	Point anchorPoint;
	Point transPoint;
	bool hasAnchor = false;
public:
	TransformTool() {
	}

	enum Params { };

	bool handleInput(InputManager *input) {
		if (!comic) return false;

		Page *page = comic->getActivePage();

		if (input->isPressed(InputManager::Keyboard, KEY_ESCAPE, true)) {
			reset();
			return true;
		}

		if (input->isPressed(InputManager::Mouse, MOUSE_BUTTON_LEFT, true)) {
			Point mouse = {input->getMouseX(true), input->getMouseY(true)};

			if (workAttachment) {
				Bound bound = workAttachment->getBound();
				Point pnt[4];
				pnt[0] = {bound.x, bound.y};
				pnt[1] = {bound.x, bound.y + bound.h};
				pnt[2] = {bound.x + bound.w, bound.y + bound.h};
				pnt[3] = {bound.x + bound.w, bound.y};
				for (int i = 0; i < 4; i++) {
					Bound bnd = {(int)(pnt[i].x - controlSize / 2),
								(int)(pnt[i].y - controlSize / 2),
								controlSize, controlSize};
					if (Bound::inside(bnd, mouse)) {
						hasAnchor = true;
						anchorPoint = pnt[(i + 2) % 4];
						transPoint = pnt[i];
						previousMouse = mouse;
						return true;
					}
				}
				if (Bound::inside(bound, mouse)) {
					hasAnchor = false;
					previousMouse = mouse;
					return true;
				}
				else {
					reset();
					return true;
				}
			}
			else {
				for (Attachment *attachment: page->getAttachments()) {
					Bound bound = attachment->getBound();
					if (Bound::inside(bound, mouse)) {
						workAttachment = attachment;
						workRatio = workAttachment->getAspectRatio();
						previousMouse = mouse;
						return true;
					}
				}
			}
		}

		if (workAttachment && input->isReleased(InputManager::Mouse, MOUSE_BUTTON_LEFT, true)) {
			// if (hasAnchor) hasAnchor = false;
			// reset();
			return true;
		}

		if (workAttachment && input->isDown(InputManager::Mouse, MOUSE_BUTTON_LEFT)) {
			bool maintainAspect = input->isOn(InputManager::Modifier::Shift);
			Point mouse = {input->getMouseX(true), input->getMouseY(true)};
			int dx = mouse.x - previousMouse.x;
			int dy = mouse.y - previousMouse.y;
			int ox = workAttachment->getX();
			int oy = workAttachment->getY();
			if (hasAnchor == false) { //Not control point
				workAttachment->setX(ox + dx);
				workAttachment->setY(oy + dy);
			}
			else {
				transPoint.x += dx; 
				transPoint.y += dy;
				
				float ratio = workRatio;

				int nw = abs(anchorPoint.x - transPoint.x);
				int nh = abs(anchorPoint.y - transPoint.y);

				if (maintainAspect) {
					if (nh * ratio <= nw)
						nw = nh * ratio;
					else if (nw / ratio <= nh)
						nh = nw / ratio;
				}

				if (anchorPoint.x >= transPoint.x) {
					workAttachment->setX(anchorPoint.x - nw);
				}

				if (anchorPoint.y >= transPoint.y) {
					workAttachment->setY(anchorPoint.y - nh);
				}

				workAttachment->setW(nw);
				workAttachment->setH(nh);
			}
			previousMouse = mouse;
			return true;
		}

		return false;
	}

	void setParam(int id, void *value) {
		switch (id) {
			default:
				break;
		}
	}

	void reset() {
		workAttachment = NULL;
		workRatio = 1.0;
		hasAnchor = false;
	}

	void update() {
		
	}

	void commit() {
		
	}

	void drawDashedLine(Point start, Point end, Color color = BLACK) {
		const int num = 40;

		Point s, e;
		for (int i = 0; i < num; i ++) {
			float t = i / (float)(num - 1);
			if (i % 2 == 0) {
				s.x = (1 - t) * start.x + t * end.x;
				s.y = (1 - t) * start.y + t * end.y;
			}
			else {
				e.x = (1 - t) * start.x + t * end.x;
				e.y = (1 - t) * start.y + t * end.y;
				DrawLine(s.x, s.y, e.x, e.y, color);
			}
		}
	}

	void draw(TextEngine *textEngine) {
		if (!workAttachment) return;

		const int size = controlSize;
		const int line = controlOutline;

		Bound bound = workAttachment->getBound();
		Point pnt[4];
		pnt[0] = {bound.x, bound.y};
		pnt[1] = {bound.x, bound.y + bound.h};
		pnt[2] = {bound.x + bound.w, bound.y + bound.h};
		pnt[3] = {bound.x + bound.w, bound.y};

		for (int i = 0; i < 4 - 1; i++)
			drawDashedLine(pnt[i], pnt[i + 1], BLACK);
		drawDashedLine(pnt[3], pnt[0]);

		for (int i = 0; i < 4; i++) {
			DrawRectangle(pnt[i].x - size / 2, pnt[i].y - size / 2, size, size, BLACK);
			DrawRectangle(pnt[i].x - size / 2 + line, pnt[i].y - size / 2 + line, size - line * 2, size - line * 2, WHITE);
		}
	}

	~TransformTool() {

	}
};