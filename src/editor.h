#pragma once

#include "comic.h"
#include "tools/tool.h"
#include "tools/slice.h"
#include "ui.h"

#define MAX_ZOOM 30
#define MIN_ZOOM 0.1
#define ZOOM_SCALE 0.1

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
	Vector2 inputDown;

	int handleWheel() {
		if (GetMouseWheelMove() != 0) {
			int zoomDelta = 1;
			zoomStops += GetMouseWheelMove() > 0 ? zoomDelta : -zoomDelta;
			Vector2 mouse = GetMousePosition();
			Vector2 preZoom = GetScreenToWorld2D(mouse, camera);
			camera.zoom = exp(zoomStops * ZOOM_SCALE);
			if (camera.zoom > MAX_ZOOM) {
				camera.zoom = MAX_ZOOM;
				zoomStops -= zoomDelta;
			}
			else if (camera.zoom < MIN_ZOOM) {
				camera.zoom = MIN_ZOOM;
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
		int wheel = handleWheel();
		int gestures = handleGestures();

		sliceTool.handleInput();
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