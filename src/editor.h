#pragma once

#include "comic.h"
#include "tools/tool.h"
#include "tools/slice.h"
#include "tools/panel.h"
#include "tools/transform.h"
#include "tools/bubble.h"
#include "tools/text.h"
#include "input_manager.h"
#include "text_engine.h"

#ifndef __EMSCRIPTEN__
	#include "ui.h"
#endif

#include <vector>
using namespace std;

class Editor {
private:
	Comic comic;
	vector<Tool*> tools;
	int activeTool = -1;

#ifndef __EMSCRIPTEN__
	UI ui;
#endif

	Camera2D camera = {.zoom = 1};
	float zoomStops = 0.0;
	const float zoomScale = 0.1;
	const float minZoom = 0.1;
	const float maxZoom = 4;
	Vector2 inputDown;

	InputManager input;
	TextEngine text;

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
	Editor()
#ifndef __EMSCRIPTEN__
	: ui(20)
#endif
	{
		tools.push_back(new SliceTool());
		tools.push_back(new PanelTool());
		tools.push_back(new TransformTool());
		tools.push_back(new BubbleTool());
		tools.push_back(new TextTool());

		for (int i = 0; i < tools.size(); i++)
			tools[i]->setTarget(&comic);
	}

	void init() {
		text.init();
		text.loadFont("ComicSans", "fonts/ComicSansMS3.ttf");
	}

	void addPage() {
		comic.addPage();
	}

	void setActivePage(int id) {
		comic.setActivePage(id);
	}

	int getAttachmentCount() {
		return comic.getAttachmentCount();
	}

	int getPanelCount() {
		return comic.getPanelCount();
	}

	int getAttachmentPanel(int id) {
		return comic.getAttachmentPanel(id);
	}

	int getAttachmentType(int id) {
		return comic.getAttachmentType(id);
	}

	void setAttachmentPanel(int id, int panel) {
		comic.setAttachmentPanel(id, panel);
	}

	void addIllust(char *path) {
		Image img = LoadImage(path);
		comic.addIllust(img);
		UnloadImage(img);
	}

	void update() {
		input.update(camera);
		int wheel = handleWheel();
		int gestures = handleGestures();

		if (activeTool > -1 && activeTool < tools.size()) {
			tools[activeTool]->handleInput(&input);
			tools[activeTool]->update();
		}

#ifndef __EMSCRIPTEN__
			ui.update(activeTool);
#endif

		comic.update();
	}

	void setActiveTool(int id) {
		activeTool = id;
	}

	void draw() {
		BeginMode2D(camera);
			comic.draw(&text);

			if (activeTool > -1 && activeTool < tools.size()) {
				tools[activeTool]->draw(&text);
			}
		EndMode2D();

#ifndef __EMSCRIPTEN__
			ui.draw();
#endif
	}

	~Editor() {
		for (int i = 0; i < tools.size(); i++)
			delete tools[i];
	}

};