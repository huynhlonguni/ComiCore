#pragma once

#include "tool.h"
#include "../path.h"
#include "raylib.h"
#include "../attachments/bubble.h"

#include <math.h>
#include <iostream>
using namespace std;

class BubbleTool : public Tool {
private:
	int controlSize = 10;
	int controlOutline = 2;

	Point previousMouse;
	Bubble bubble;
	Point startPoint;
	bool started = false;
public:
	BubbleTool() {
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
			started = true;
			startPoint = mouse;
		}

		if (input->isReleased(InputManager::Mouse, MOUSE_BUTTON_LEFT, true)) {
			commit();
			reset();
			return true;
		}

		if (input->isDown(InputManager::Mouse, MOUSE_BUTTON_LEFT)) {
			Point mouse = {input->getMouseX(true), input->getMouseY(true)};
			
			Path pnts(2);
			pnts[0] = mouse;
			pnts[1] = startPoint;

			Bound bound = Bound::fromPoints(pnts);

			bubble.setBound(bound);

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
		started = false;
	}

	void update() {
		
	}

	void commit() {
		if (comic)
			comic->addBubble(bubble);
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

	void draw() {
		if (!started) return;

		const int size = controlSize;
		const int line = controlOutline;

		Bound bound = bubble.getBound();
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

		bubble.draw();
	}

	~BubbleTool() {

	}
};