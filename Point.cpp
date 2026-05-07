#include "Point.hpp"
#include <iostream>
#include <functional>
#include <cmath>

double Point::distanceTo(const Point& other) const {
	double distanceX = x - other.x;
	double distanceY = y - other.y;
	return std::sqrt(distanceX * distanceX + distanceY * distanceY);
}

bool Point::isOnStraightLineWith(const Point& point2, const Point& point3) const {
	// векторное произведение векторов в координатах
	return (point2.y - y) * (point3.x - point2.x) == (point3.y - point2.y) * (point2.x - x);
}

bool Point::isOnStraightLineWith(const Point& point2, const Point& point3, double accuracy) const {
	// векторное произведение векторов в координатах
	double vectorMultiply = (point2.x - x) * (point3.y - point2.y) - (point3.x - point2.x) * (point2.y - y);
	if (vectorMultiply < 0) {
		vectorMultiply *= -1;
	}
	std::cout << vectorMultiply << " ";
	return vectorMultiply <= accuracy;
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
	return hashX ^ (hashY * 0x9e3779b9 + (hashX << 6) + (hashX >> 2));
	// return hashX ^ (hashY << 1);
}
