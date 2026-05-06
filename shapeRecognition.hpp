#ifndef SHAPE_RECOGNIZER_HPP
#define SHAPE_RECOGNIZER_HPP

#include <iostream>
#include <unordered_set>
#include <vector>
#include "Point.hpp"

bool isPointInContour(size_t width, size_t height, const std::vector<bool>& allPoints, const Point& point);

void findShapeContourRecursive(
	size_t width,
	size_t height,
	const std::vector<bool> &allPoints,
	std::vector<Point> &vecContour,
	std::unordered_set<Point, PointHash> &setVisitedPoints,
	const Point &point
);

void recognizeShapes(std::istream &is, std::ostream &os, size_t width, size_t height);

#endif
