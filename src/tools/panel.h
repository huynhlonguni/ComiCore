#pragma once

#include "tool.h"
#include "../path.h"
#include "raylib.h"

#include <math.h>
#include <iostream>
using namespace std;

class PanelTool : public Tool {
private:
	int controlSize = 10;
	int controlOutline = 2;

	Point previousMouse;
	Panel *workPanel = NULL;
	Point *workPoint = NULL;
public:
	PanelTool() {
	}

	enum Params { };

	bool handleInput(InputManager *input) {
		if (!comic) return false;

		Page *page = comic->getActivePage();

		if (input->isPressed(InputManager::Mouse, MOUSE_BUTTON_LEFT, true)) {
			Point mouse = {input->getMouseX(true), input->getMouseY(true)};
			for (Panel &panel: page->getPanels()) {
				for (Path &path: panel.getPaths()) {
					for (Point &pnt: path) {
						if (mouse.x >= pnt.x - controlSize / 2 && mouse.x <= pnt.x + controlSize / 2
						&& mouse.y >= pnt.y - controlSize / 2 && mouse.y <= pnt.y + controlSize / 2) {
							workPoint = &pnt;
							workPanel = &panel;
							previousMouse = mouse;
							return true; //early return and let next frame handle drag
						}

					}
				}
			}
		}

		if (workPoint && input->isReleased(InputManager::Mouse, MOUSE_BUTTON_LEFT, true)) {
			reset();
			return true;
		}

		if (workPoint && input->isDown(InputManager::Mouse, MOUSE_BUTTON_LEFT)) {
			Point mouse = {input->getMouseX(true), input->getMouseY(true)};
			workPoint->x += mouse.x - previousMouse.x;
			workPoint->y += mouse.y - previousMouse.y;
			previousMouse = mouse;
			workPanel->triangulate();
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
		workPoint = NULL;
		workPanel = NULL;
	}

	void update() {
		
	}

	void commit() {
		
	}

	void draw(TextEngine *textEngine) {
		if (!comic) return;

		const int size = controlSize;
		const int line = controlOutline;

		Page *page = comic->getActivePage();

		for (Panel &panel: page->getPanels()) {
			for (Path &path: panel.getPaths()) {
				for (Point &pnt: path) {
					DrawRectangle(pnt.x - size / 2, pnt.y - size / 2, size, size, BLACK);
					DrawRectangle(pnt.x - size / 2 + line, pnt.y - size / 2 + line, size - line * 2, size - line * 2, WHITE);
				}
			}
		}
	}

	~PanelTool() {

	}
};