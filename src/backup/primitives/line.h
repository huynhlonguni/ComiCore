#pragma once

#include "point.h"

class Line {
public:
	Point s = {0, 0};
	Point e = {0, 0};
public:
	Line() {}
	Line(Point s, Point e) : s(s), e(e) {
	}

	static bool getSide(Line line, Point p) {
		double dx = line.e.x - line.s.x;
		double dy = line.e.y - line.s.y;

		double px = p.x - line.s.y;
		double py = p.y - line.s.y;

		double cross = dx * py - dy * px;

		if (cross == 0) return 0;
		if (cross < 0) return -1;
		if (cross > 0) return 1;
	}

	static Point getIntersection(Line l1, Line l2) {

	}

	static void draw(Point s, Point e, Color color = BLACK) {
		DrawLine(s.x, s.y, e.x, e.y, color);
	}

	static void draw(Line l, Color color = BLACK) {
		Line::draw(l.s, l.e, color);
	}
};