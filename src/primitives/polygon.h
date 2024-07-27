#pragma once

#include "point.h"
#include "line.h"

#include <vector>
using namespace std;

class Polygon {
public:
	vector<Point> pnts;
	vector<Line> edges;
private:
	void genEdges() {
		const int n = pnts.size();

		vector<Line> edges(n);

		for (int i = 0; i < n - 1; i++) {
			edges[i] = Line(pnts[i], pnts[i + 1]);
		}
		edges[n - 1] = Line(pnts[n - 1], pnts[0]);
	}
public:
	Polygon() {}

	Polygon(vector<Point> points) : pnts(points) {}

	vector<Point> getPoints() {
		return pnts;
	}

	vector<Line> getEdges() {
		return edges;
	}

	static void draw(vector<Point> pnts, Color color = BLACK) {
		const int n = pnts.size();

		if (n == 0) return;

		if (n == 1) return Point::draw(pnts[0], color);

		if (n == 2) return Line::draw(pnts[0], pnts[1], color);

		for (int i = 0; i < n - 1; i++) {
			Line::draw(pnts[i], pnts[i + 1], color);
		}
		Line::draw(pnts[n - 1], pnts[0], color);
	}

	static void draw(Polygon poly, Color color = BLACK) {
		Polygon::draw(poly.pnts, color);
	}
};