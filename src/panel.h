#pragma once

#include "path.h"
#include "bound.h"

#include "earcut.h"
#include "raylib.h"

#include <vector>
#include <iostream>
using namespace std;

namespace mapbox {
	namespace util {
		template <>
		struct nth<0, Point> {
			inline static auto get(const Point &t) {
				return t.x;
			};
		};
		template <>
		struct nth<1, Point> {
			inline static auto get(const Point &t) {
				return t.y;
			};
		};
	}
}

class Panel {
private:
	Paths paths;
	Bound bound;

	// Color color;

	int thickness = 1;

	vector<unsigned short> triangles;
	Path vertices;
public:
	void triangulate() {
		vertices.clear();
		triangles = mapbox::earcut<unsigned short>(paths);
		for (const Path &p: paths)
			vertices.insert(vertices.end(), p.begin(), p.end());
	}


	Panel(const Paths paths) : paths(paths) {
		// bound = Bound::fromPoints(paths);
		// const Color colors[] = {GRAY, DARKGRAY, ORANGE, PINK, RED, MAROON, DARKGREEN, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN};
		// int ind = GetRandomValue(0, sizeof(colors) / sizeof(colors[0]));
		// color = colors[ind];
		triangulate();
	}

	Bound getBound() {
		return bound;
	}

	Paths& getPaths() {
		return paths;
	}

	void drawMask() {
		for (int i = 0; i < triangles.size(); i += 3) {
			Point p3 = vertices[triangles[i + 0]];
			Point p2 = vertices[triangles[i + 1]];
			Point p1 = vertices[triangles[i + 2]];
			DrawTriangle({(float)p1.x, (float)p1.y}, {(float)p2.x, (float)p2.y}, {(float)p3.x, (float)p3.y}, {128, 128, 128, 128});
		}
	}

	void drawLine(Point a, Point b, Color color = BLACK) {
		Vector2 start = {(float)a.x, (float)a.y};
		Vector2 end = {(float)b.x, (float)b.y};
		// DrawRectangleV({start.x - thickness / 2, start.y - thickness / 2}, {thickness, thickness}, color);
		// DrawRectangleV({end.x - thickness / 2, end.y - thickness / 2}, {thickness, thickness}, color);
		DrawLineEx(start, end, thickness, color);
	}

	void draw(Color color = BLACK) {
		for (Path &p: paths) {
			for (int i = 0; i < p.size() - 1; i++) {
				drawLine(p[i], p[i + 1], color);
			}
			drawLine(p[p.size() - 1], p[0], color);
		}
		Renderer::draw(paths, true, color);
	}
};