#pragma once

#include "primitives/point.h"
#include "primitives/line.h"
#include "panel.h"
#include "bound.h"
#include "polygon_splitter.h"
#include "raylib.h"

#include <vector>
#include <iostream>
using namespace std;

class Page {
private:
	vector<Panel> panels;
	int width = 0;
	int height = 0;

	Camera2D camera = {.zoom = 1};
	float zoomStops = 0.0;
	Vector2 inputDown;

	Panel getDefaultPanel(int width, int height, int paddingX = 20, int paddingY = 20) {
		vector<Point> points(4);
		//Counter clockwise
		points[0] = {(CoordType)paddingX, (CoordType)paddingY};
		points[1] = {(CoordType)paddingX, (CoordType)height - paddingY};
		points[2] = {(CoordType)width - paddingX, (CoordType)height - paddingY};
		points[3] = {(CoordType)width - paddingX, (CoordType)paddingY};

		return Panel(points);
	}

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
	Page() {}
	Page(int width, int height) : panels(1), width(width), height(height) {
		panels[0] = getDefaultPanel(width, height);
	}

	void update() {
		int wheel = handleWheel();
		int gestures = handleGestures();
	}

	void draw() {
		BeginMode2D(camera);
			DrawRectangle(0, 0, width, height, WHITE);

			for (int i = 0; i < panels.size(); i++) {
				panels[i].draw();
			}
		EndMode2D();
	}

	void slice(vector<Point> line) {

		vector<Panel> res;

		Bound cutBound = Bound::fromPoints(line);

		for (int i = 0; i < panels.size(); i++) {
			Panel &panel = panels[i];

			if (!Bound::intersect(cutBound, panel.getBound())) {
				cout << "Doesnt intersect" << endl;
				res.push_back(panel);
				continue;
			}

			vector<Panel> splits = PolygonSplitter::split(panel, line);
			cout << "Split: " << splits.size() << endl;
			res.insert(res.end(), splits.begin(), splits.end());
		}

		panels = res;
	}
};