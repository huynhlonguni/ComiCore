#pragma once

#include "raylib.h"

#include "../primitives/point.h"
#include "../primitives/line.h"
#include "../primitives/polygon.h"

class PointRenderer {
public:
	static void draw(Point p, Color color = BLACK) {
		DrawPixel(p.x, p.y, color);
	} 
};

class LineRenderer {
public:
	static void draw(Point s, Point e, Color color = BLACK) {
		DrawLine(s.x, s.y, e.x, e.y, color);
	}

	static void draw(Line l, Color color = BLACK) {
		LineRenderer::draw(l.s, l.e, color);
	}
};