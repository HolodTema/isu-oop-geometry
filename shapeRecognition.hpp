#ifndef SHAPE_RECOGNIZER_HPP
#define SHAPE_RECOGNIZER_HPP

#include <iostream>
#include <vector>
#include "Point.hpp"

bool isPointInContour(size_t width, size_t height, const std::vector<bool>& allPoints, const Point& point);

std::vector<Point> findShapeContour(
	size_t width,
	size_t height,
	const std::vector<bool> &allPoints,
	const Point& startPoint
);

void recognizeShapes(std::istream &is, std::ostream &os, size_t width, size_t height, bool debugMode);

#endif
