#ifndef SHAPE_RECOGNIZER_HPP
#define SHAPE_RECOGNIZER_HPP

#include <iostream>
#include <unordered_set>
#include <vector>
#include "Point.hpp"
#include "Polygon.hpp"

static bool isPointInContour(size_t width, size_t height, bool* allPoints, const Point& point) {
	if (!allPoints[point.y * width + point.x]) {
		return false;
	}
	bool hasRightNeighbour = (point.x - 1 >= 0) && allPoints[point.y * width + point.x - 1];
	bool hasLeftNeighbour = (point.x + 1 < width) && allPoints[point.y * width + point.x + 1];
	bool hasTopNeighbour = (point.y - 1 >= 0) && allPoints[(point.y - 1) * width + point.x];
	bool hasBottomNeighbour = (point.y + 1 < height) && allPoints[(point.y + 1) * width + point.x];

	return (hasBottomNeighbour && hasLeftNeighbour) ||
		   (hasBottomNeighbour && hasRightNeighbour) ||
		   (hasLeftNeighbour && hasTopNeighbour) ||
		   (hasRightNeighbour && hasTopNeighbour);
}

static void findShapeContourRecursive(
	size_t width,
	size_t height,
	bool* allPoints,
	std::vector<Point> &vecContour,
    std::unordered_set<Point, PointHash> &setVisitedPoints,
	const Point &point
) {
	bool value = allPoints[point.y * width + point.x];
	if (!value) {
		return;
	}
	if (setVisitedPoints.find(point) == setVisitedPoints.end()) {
		return;
	}

	setVisitedPoints.insert(point);

	if (isPointInContour(width, height, allPoints, point)) {
		vecContour.push_back(point);
	}

	if (point.x > 0) {
		findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, Point(point.x - 1, point.y));
	}
	if (point.x < width - 1) {
		findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, Point(point.x + 1, point.y));
	}
	if (point.y > 0) {
		findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, Point(point.x, point.y - 1));
	}
	if (point.y < height - 1) {
		findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, Point(point.x, point.y + 1));
	}
}

void recognizeShapes(std::istream &is, std::ostream &os, size_t width, size_t height) {
	bool *allPoints = new bool[width * height];
	int pointValue = 0;
	for (size_t i = 0; i < width * height; ++i) {
		is >> pointValue;
		allPoints[i] = pointValue == 1;
	}

	std::unordered_set<Point, PointHash> setVisitedPoints(width * height);

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			bool value = allPoints[y * width + x];
			Point point = Point(x, y);
			std::vector<Point> vecContour;
			if (value && setVisitedPoints.find(point) == setVisitedPoints.end()) {
				findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, point);

			}
		}
	}

	delete[] allPoints;
}

#endif
