#include "Point.hpp"
#include <iostream>

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
