#pragma once

#include "tool.h"
#include "../path.h"
#include "raylib.h"
#include "../attachments/text.h"

#include <math.h>
#include <iostream>
using namespace std;

class TextTool : public Tool {
private:
	bool started = false;
	Point startPoint;

	Text text;
public:
	TextTool() {
	}

	enum Params { };

	bool handleInput(InputManager *input) {
		if (!comic) return false;

		Page *page = comic->getActivePage();

		if (input->isPressed(InputManager::Keyboard, KEY_ESCAPE, true)) {
			reset();
			return true;
		}

		if (input->isPressed(InputManager::Keyboard, KEY_ENTER, true)) {
			commit();
			reset();
			return true;
		}

		if (input->isPressed(InputManager::Mouse, MOUSE_BUTTON_LEFT, true)) {
			Point mouse = {input->getMouseX(true), input->getMouseY(true)};
			started = true;
			text.setX(mouse.x);
			text.setY(mouse.y);
			text.setFont("ComicSans");
			text.setSize(40.0);
			text.setContent("");
		}

		if (started) {
			int key = GetCharPressed();

			while (key > 0) {
				if ((key >= 32) && (key <= 125)) {
					string content = text.getContent();
					content += (char)key;
					text.setContent(content);
				}
				key = GetCharPressed();  // Check next character in the queue
			}

			if (input->isPressed(InputManager::Keyboard, KEY_BACKSPACE, true)) {
				string content = text.getContent();
				if (content.size())
					content.pop_back();
				text.setContent(content);
			}
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
			comic->addText(text);
	}

	void draw(TextEngine *textEngine) {
		if (!started) return;

		text.draw(textEngine);

		// const int size = controlSize;
		// const int line = controlOutline;

		// Bound bound = text.getBound();
		// Point pnt[4];
		// pnt[0] = {bound.x, bound.y};
		// pnt[1] = {bound.x, bound.y + bound.h};
		// pnt[2] = {bound.x + bound.w, bound.y + bound.h};
		// pnt[3] = {bound.x + bound.w, bound.y};

		// for (int i = 0; i < 4 - 1; i++)
		// 	drawDashedLine(pnt[i], pnt[i + 1], BLACK);
		// drawDashedLine(pnt[3], pnt[0]);

		// for (int i = 0; i < 4; i++) {
		// 	DrawRectangle(pnt[i].x - size / 2, pnt[i].y - size / 2, size, size, BLACK);
		// 	DrawRectangle(pnt[i].x - size / 2 + line, pnt[i].y - size / 2 + line, size - line * 2, size - line * 2, WHITE);
		// }

		// bubble.draw();
	}

	~TextTool() {

	}
};