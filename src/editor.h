#pragma once

#include "comic.h"
#include "tools/tool.h"
#include "tools/slice.h"
#include "ui.h"
#include "input_manager.h"

#include <vector>
using namespace std;

class Editor {
private:
	Comic comic;
	vector<Tool*> tools;
	SliceTool sliceTool;

	UI ui;
	const bool usesUI = true;

	Camera2D camera = {.zoom = 1};
	float zoomStops = 0.0;
	const float zoomScale = 0.1;
	const float minZoom = 0.1;
	const float maxZoom = 4;
	Vector2 inputDown;

	InputManager input;

	int handleWheel() {
		if (GetMouseWheelMove() != 0) {
			int zoomDelta = 1;
			zoomStops += GetMouseWheelMove() > 0 ? zoomDelta : -zoomDelta;
			Vector2 mouse = GetMousePosition();
			Vector2 preZoom = GetScreenToWorld2D(mouse, camera);
			camera.zoom = exp(zoomStops * zoomScale);
			if (camera.zoom > maxZoom) {
				camera.zoom = maxZoom;
				zoomStops -= zoomDelta;
			}
			else if (camera.zoom < minZoom) {
				camera.zoom = minZoom;
				zoomStops += zoomDelta;
			}
			Vector2 postZoom = GetWorldToScreen2D(preZoom, camera);
			camera.offset.x += mouse.x - postZoom.x;
			camera.offset.y += mouse.y - postZoom.y;
			return 1;
		}
		return 0;
	}

	int handleGestures() {
		int currentGesture = GetGestureDetected();

		if (currentGesture == GESTURE_TAP) {
			inputDown = GetTouchPosition(0);
		}
		else if (currentGesture == GESTURE_DRAG) {
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
				Vector2 delta = Vector2Subtract(GetTouchPosition(0), inputDown);
				camera.offset.x += delta.x;
				camera.offset.y += delta.y;
				inputDown = GetTouchPosition(0);
			}
		}
		return currentGesture;
	}
public:
	Editor() : ui(20) {
		sliceTool.setTarget(&comic);
	}

	void update() {
		input.update(camera);
		int wheel = handleWheel();
		int gestures = handleGestures();

		sliceTool.handleInput(&input);
		sliceTool.update();

		if (usesUI)
			ui.update();

		comic.update();
	}

	void draw() {
		BeginMode2D(camera);
			comic.draw();

			sliceTool.draw();
		EndMode2D();

		if (usesUI)
			ui.draw();

	}

};