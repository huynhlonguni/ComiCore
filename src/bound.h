#pragma once

#include "primitives/point.h"

#include <vector>
#include <iostream>
using namespace std;

class Bound {
public:
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

public:
	Bound() {}

	Bound(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {
	}

	static Bound fromPoints(Point *pnts, unsigned int n) {
		if (n == 0) return {};

		int minx = pnts[0].x;
		int maxx = pnts[0].x;

		int miny = pnts[0].y;
		int maxy = pnts[0].y;

		for (int i = 1; i < n; i++) {
			Point &p = pnts[i];

			if (p.x < minx) minx = p.x;
			if (p.x > maxx) maxx = p.x;

			if (p.y < miny) miny = p.y;
			if (p.y > maxy) maxy = p.y;
		}

		return {minx, miny, maxx - minx, maxy - miny};
	}

	static Bound fromPoints(vector<Point> pnts) {
		return fromPoints(pnts.data(), pnts.size());
	}

	static bool intersect(Bound b1, Bound b2) {
		if (b1.w == 0 || b1.h == 0 || b2.w == 0 || b2.h == 0) {
			cout << "Area 0\n";
			return false;
		}

		if (b2.x > b1.x + b1.w || b1.x > b2.x + b2.w) {
			cout << "Side 0\n";
			return false;
		}

		if (b2.y > b1.y + b1.h || b1.y > b2.y + b2.h) {
			cout << "Side 1\n";
			return false;
		}

		return true;
	}
};