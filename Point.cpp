#include "Point.hpp"
#include <iostream>

#include <cmath>

double Point::distanceTo(const Point& other) const {
	double distanceX = x - other.x;
	double distanceY = y - other.y;
	return std::sqrt(distanceX * distanceX + distanceY * distanceY);
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
