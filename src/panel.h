#pragma once

#include "primitives/polygon.h"
#include "bound.h"

#include <vector>
using namespace std;

class Panel {
private:
	Polygon poly;
	Bound bound;

public:
	Panel() {}

	Panel(vector<Point> points) : poly(points) {
		bound = Bound::fromPoints(points);
	}

	Bound getBound() {
		return bound;
	}

	Polygon getPolygon() {
		return poly;
	}

	void draw(Color color = BLACK) {
		Polygon::draw(poly, color);
	}
};