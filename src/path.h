#pragma once

#include "clipper2/clipper.h"

namespace Clipper = Clipper2Lib;

typedef Clipper::Point64 Point;
typedef Clipper::Path64 Path;
typedef Clipper::Paths64 Paths;
typedef Clipper::Rect64 Rect;

#include "raylib.h"

class Renderer {
public:
	static void draw(Point pnt, Color color = BLACK) {
		DrawPixel(pnt.x, pnt.y, color);
	}

	static void draw(Path path, bool close = false, Color color = BLACK) {
		const int n = path.size();
		for (int i = 0; i < n - 1; i++) {
			DrawLine(path[i].x, path[i].y, path[i+1].x, path[i+1].y, color);
		}
		if (close)
			DrawLine(path[n - 1].x, path[n - 1].y, path[0].x, path[0].y, color);
	}

	static void draw(Paths paths, bool close = false, Color color = BLACK) {
		for (const Path &path: paths) {
			draw(path, close, color);
		}
	}
};
