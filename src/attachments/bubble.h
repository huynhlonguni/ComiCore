#pragma once

#include "attachment.h"

class Bubble : public Attachment {
private:
	int thickness = 5;
	int padding = 10;
	float angle = 135.0; 
public:
	void DrawEllipseLinesEx(int cx, int cy, float rh, float rv, float thick, Color color) {
		const int off = 1;
		for (int i = 0; i < 360; i += off) {
			Vector2 start = {cx + cosf(DEG2RAD*(i + off))*rh, cy + sinf(DEG2RAD*(i + off))*rv};
			Vector2 end = {cx + cosf(DEG2RAD*(i))*rh, cy + sinf(DEG2RAD*(i))*rv};
			DrawLineEx(start, end, thick, color);
		}
	}

	void draw() {
		Bound bound = this->getBound();

		int cx = bound.x + bound.w / 2;
		int cy = bound.y + bound.h / 2;
		float rh = bound.w / 2.0 - padding; 
		float rv = bound.h / 2.0 - padding; 
		DrawEllipse(cx, cy, rh, rv, WHITE);
		DrawEllipseLinesEx(cx, cy, rh, rv, thickness, BLACK);
	}
};