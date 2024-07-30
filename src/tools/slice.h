#pragma once

#include "tool.h"
#include "../path.h"
#include "raylib.h"

#include <math.h>
#include <iostream>
using namespace std;

class SliceTool : public Tool {
private:
	Paths sliceLines;
	Paths inflatedSlices;

	int thickness = 20;
	int tolerance = 5;

	bool isClosedPath(bool noTempPoint = true) {
		const int n = sliceLines[0].size();
		if (n < 4 + noTempPoint) //Need 4 point to make a closed triangle
			return false;
		return sliceLines[0].front() == sliceLines[0][n - 1 - noTempPoint];
	}

	bool started(int numPoint = 0) {
		return sliceLines[0].size() > numPoint + 1; //first point is temp point
	}
public:
	SliceTool() : sliceLines(1) {
		sliceLines[0] = Path(1); //first point is temp point
	}

	enum Params { Thickness, Tolerance };

	bool handleInput(InputManager *input) {
		bool res = false;

		//Cancel on escape
		if (input->isPressed(InputManager::Keyboard, KEY_ESCAPE, true)) {
			reset();
			return true;
		}

		//Backtrack on backspace
		if (input->isPressed(InputManager::Keyboard, KEY_BACKSPACE, true)) {
			if (!started(1)) {
				reset();
				return true;
			}

			Point tmpPoint = sliceLines[0].back();
			sliceLines[0].pop_back();
			sliceLines[0].back() = tmpPoint;
			return true;
		}

		Point mouse = {input->getMouseX(true), input->getMouseY(true)};
		if (started()) {
			Point firstPoint = sliceLines[0][0];
			if (abs(mouse.x - firstPoint.x) < tolerance && abs(mouse.y - firstPoint.y) < tolerance) 
				mouse = firstPoint;

			sliceLines[0].back() = mouse;
		}

		if (input->isPressed(InputManager::Mouse, MOUSE_BUTTON_LEFT, true)) {
			sliceLines[0].back() = mouse;
			sliceLines[0].push_back(mouse);
			res = true;
		}

		if (input->getGesture(true) == GESTURE_DOUBLETAP || isClosedPath()) {
			if (started(2)) //prevent empty point on double click
				commit();
			reset();
			res = true;
		}

		return res;
	}

	void setParam(int id, void *value) {
		switch (id) {
			case Params::Thickness:
				thickness = *(int*)value;
				break;
			case Params::Tolerance:
				tolerance = *(int*)value;
				break;
			default:
				break;
		}
	}

	void reset() {
		sliceLines[0].resize(1);
		inflatedSlices.clear();
	}

	void update() {
		if (sliceLines[0].size() < 2) return;

		Clipper::JoinType joinType = Clipper::JoinType::Miter;
		Clipper::EndType endType = Clipper::EndType::Butt;
		if (isClosedPath(false))
			endType = Clipper::EndType::Joined;

		inflatedSlices = Clipper::InflatePaths(sliceLines, thickness / 2.0, joinType, endType);
	}

	void commit() {
		if (comic) {
			comic->getActivePage()->slice(inflatedSlices);
		}
	}

	void draw(TextEngine *textEngine) {
		Renderer::draw(sliceLines[0], false, BLACK);
		Renderer::draw(inflatedSlices, true, BLUE);
	}

	~SliceTool() {

	}
};