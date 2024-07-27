#pragma once

#include "raylib.h"
#include <float.h> // FLT_EPSILON

#define CoordType float

class Point {
public:
	CoordType x = 0;
	CoordType y = 0;
public:
	Point() {}
	
	Point(CoordType x, CoordType y) : x(x), y(y) {}

	static void draw(Point p, Color color = BLACK) {
		DrawPixel(p.x, p.y, color);
	}

	bool operator==(const Point &other) const {
		return fabsf(x - other.x) < FLT_EPSILON && fabsf(y - other.y) < FLT_EPSILON;
	}
};