#ifndef SHAPE_RECOGNIZER_HPP
#define SHAPE_RECOGNIZER_HPP

#include <iostream>
#include <unordered_set>
#include <vector>
#include "Point.hpp"
#include "Polygon.hpp"

bool isPointInContour(size_t width, size_t height, bool* allPoints, const Point& point) {
	int x = point.x;
	int y = point.y;
	if (!allPoints[y * width + x]) {
		return false;
	}
	bool hasRightNeighbour = (x - 1 >= 0) && allPoints[y * width + x - 1];
	bool hasLeftNeighbour = (x + 1 < width) && allPoints[y * width + x + 1];
	bool hasTopNeighbour = (y - 1 >= 0) && allPoints[(y - 1) * width + x];
	bool hasBottomNeighbour = (y + 1 < height) && allPoints[(y + 1) * width + x];
	return (hasBottomNeighbour && hasLeftNeighbour) ||
		   (hasBottomNeighbour && hasRightNeighbour) ||
		   (hasLeftNeighbour && hasTopNeighbour) ||
		   (hasRightNeighbour && hasTopNeighbour);
}

void findShapeContourRecursive(
	size_t width,
	size_t height,
	bool* allPoints,
	std::vector<Point>& vecContour,
    std::unordered_set<Point, PointHash>& setVisitedPoints,
	const Point& point
) {
	int x = point.x;
	int y = point.y;

	if (setVisitedPoints.find(point) != setVisitedPoints.end()) {
		return;
	}

	setVisitedPoints.insert(point);

	if (x < width - 1) {
		Point pointRight = Point(x + 1, y);
		if (isPointInContour(width, height, allPoints, pointRight)) {
			vecContour.push_back(pointRight);
			findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointRight);
			return;
		}
	}
	if (x > 0) {
		Point pointLeft = Point(x - 1, y);
		if (isPointInContour(width, height, allPoints, pointLeft)) {
			vecContour.push_back(pointLeft);
			findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointLeft);
			return;
		}
	}
	if (y > 0) {
		Point pointTop = Point(x, y - 1);
		if (isPointInContour(width, height, allPoints, pointTop)) {
			vecContour.push_back(pointTop);
			findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointTop);
			return;
		}
	}
	if (y < height - 1) {
		Point pointBottom = Point(x, y + 1);
		if (isPointInContour(width, height, allPoints, pointBottom)) {
			vecContour.push_back(pointBottom);
			findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointBottom);
			return;
		}
	}
}

void recognizeShapes(std::istream &is, std::ostream &os, size_t width, size_t height) {
	bool *allPoints = new bool[width * height];
	bool pointValue = false;
	for (size_t i = 0; i < width * height; ++i) {
		is >> pointValue;
		allPoints[i] = pointValue;
	}

	std::unordered_set<Point, PointHash> setVisitedPoints(width * height);

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			bool value = allPoints[y * width + x];
			Point point = Point(x, y);
			std::vector<Point> vecContour;
			if (value) {
				if (isPointInContour(width, height, allPoints, point)) {
					if (setVisitedPoints.find(point) == setVisitedPoints.end()) {
						vecContour.push_back(point);
						findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, point);
						Polygon polygon(vecContour);
						size_t amountApproximatedVertices = polygon.approximateVertices();
						os << "optimized: " << amountApproximatedVertices << "\n";
						os << "vertices left " << polygon.getNumberVertices() << "\n";
						os << "------------------\n\n";
					}
				}
			}
		}
	}

	delete[] allPoints;
}

#endif
