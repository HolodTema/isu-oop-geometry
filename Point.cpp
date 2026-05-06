#include "Point.hpp"
#include <iostream>

#include <cmath>

double Point::distanceTo(const Point& other) const {
	double distanceX = x - other.x;
	double distanceY = y - other.y;
	return std::sqrt(distanceX * distanceX + distanceY * distanceY);
}

bool Point::isOnStraightLineWith(const Point& point2, const Point& point3) const {
	double k1 = (point2.y - y) / (point2.x - x);
	double k2 = (point3.y - point2.y) / (point3.x - point2.x);
	return k1 == k2;
}

bool Point::operator==(const Point& other) const {
	return x == other.x && y == other.y;
}

std::istream& operator>>(std::istream& is, Point& point) {
	std::istream::sentry s(is);
	if (!s) {
		return is;
	}
	is >> point.x;
	is >> point.y;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
	std::ostream::sentry s(os);
	if (!s) {
		return os;
	}
	os << "(" << point.x << ", " << point.y << ")";
	return os;
}

size_t PointHash::operator()(const Point& point) const {
	size_t hashX = std::hash<double>{}(point.x);
	size_t hashY = std::hash<double>{}(point.y);
	return hashX ^ (hashY << 1);
}
