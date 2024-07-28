#pragma once

#include "primitives/point.h"
#include "primitives/line.h"
#include "primitives/polygon.h"
#include "polypartition.h"
#include "panel.h"

#include "clipper2/clipper.h"

#include <math.h>
#include <float.h> // FLT_EPSILON

#include <vector>
#include <list>
using namespace std; 

class PolygonSplitter {
public:
	enum LineIntersectionType {
		LINE_NO_INTERSECT = 0,
		LINE_INTERSECT_INSIDE,
		LINE_INTERSECT_ENDPOINT,
		LINE_INTERSECT_OVERLAP,
	};

	static LineIntersectionType lineIntersect(Line edge, Line cut, Point &intersectionPoint) {
		float div = (cut.e.y - cut.s.y)*(edge.e.x - edge.s.x) - (cut.e.x - cut.s.x)*(edge.e.y - edge.s.y);

		if (fabsf(div) >= FLT_EPSILON) {
			Point ip;
			ip.x = ((cut.s.x - cut.e.x)*(edge.s.x*edge.e.y - edge.s.y*edge.e.x) - (edge.s.x - edge.e.x)*(cut.s.x*cut.e.y - cut.s.y*cut.e.x))/div;
			ip.y = ((cut.s.y - cut.e.y)*(edge.s.x*edge.e.y - edge.s.y*edge.e.x) - (edge.s.y - edge.e.y)*(cut.s.x*cut.e.y - cut.s.y*cut.e.x))/div;

			if (((fabsf(edge.s.x - edge.e.x) > FLT_EPSILON) && (ip.x < fminf(edge.s.x, edge.e.x) || (ip.x > fmaxf(edge.s.x, edge.e.x)))) ||
				((fabsf(cut.s.x - cut.e.x) > FLT_EPSILON) && (ip.x < fminf(cut.s.x, cut.e.x) || (ip.x > fmaxf(cut.s.x, cut.e.x)))) ||
				((fabsf(edge.s.y - edge.e.y) > FLT_EPSILON) && (ip.y < fminf(edge.s.y, edge.e.y) || (ip.y > fmaxf(edge.s.y, edge.e.y)))) ||
				((fabsf(cut.s.y - cut.e.y) > FLT_EPSILON) && (ip.y < fminf(cut.s.y, cut.e.y) || (ip.y > fmaxf(cut.s.y, cut.e.y)))))
				return LINE_NO_INTERSECT;

			if (ip == edge.s) {
				intersectionPoint = edge.s;
				return LINE_INTERSECT_ENDPOINT;
			}
			else if (ip == edge.e) {
				intersectionPoint = edge.e;
				return LINE_INTERSECT_ENDPOINT;
			}
			else {
				intersectionPoint = ip;
				return LINE_INTERSECT_INSIDE;
			}
		}
		else {
			div = (cut.e.y - edge.s.y)*(cut.e.x - edge.s.x) - (cut.e.x - edge.s.x)*(cut.e.y - edge.s.y);
			if (fabsf(div) < FLT_EPSILON)
				return LINE_INTERSECT_OVERLAP;
		}

		return LINE_NO_INTERSECT;
	}

	static vector<Panel> split(Panel panel, Path split) {
		// vector<Line> edges = panel.getPolygon().getEdges();

		Clipper2Lib::PathsD subject, solution;
		Clipper2Lib::PathD sub;
		for (const Point &p : panel.getPolygon().getPoints()) {
			sub.push_back({p.x, p.y}); 
		}
		subject.push_back(sub);

		const int thickness = 20;
		Clipper2Lib::PathsD polyline(1), inflatedLine;
		for (int i = 0; i < split.size(); i++) {
			polyline[0].push_back({split[i].x, split[i].y});
		}
		inflatedLine = Clipper2Lib::InflatePaths(polyline, thickness / 2.0, Clipper2Lib::JoinType::Miter, Clipper2Lib::EndType::Square);

		solution = Clipper2Lib::Difference(subject, inflatedLine, Clipper2Lib::FillRule::NonZero);

		vector<Panel> res;

		for (const Clipper2Lib::PathD &sol : solution) {
			vector<Point> pnts;
			for (const Clipper2Lib::PointD &pnt: sol) {
				pnts.push_back({pnt.x, pnt.y});
			}
			res.push_back(pnts);
		}
		return res;

		// list<TPPLPoly> polys(1);
		// vector<TPPLPoint> pnts;
		// bool doIntersect = false;

		// for (Line &e : edges) {
		// 	for (Line &l : split) {
		// 		pnts.push_back({e.s.x, e.s.y});
		// 		Point ip;
		// 		LineIntersectionType t = lineIntersect(e, l, ip);
		// 		if (t == LINE_INTERSECT_ENDPOINT || t == LINE_INTERSECT_INSIDE) {
		// 			doIntersect = true;
		// 		}
		// 	}
		// }
		return {};
	}
};