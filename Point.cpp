#include "Point.hpp"
#include <iostream>
#include <functional>
#include <cmath>

double Point::distanceTo(const Point& other) const {
	double distanceX = x - other.x;
	double distanceY = y - other.y;
	return std::sqrt(distanceX * distanceX + distanceY * distanceY);
}

// double Point::distanceToSegment(const Point& point1, const Point& point2) const {
// 	//point1 и point2 точки отрезка
// 	// находим коэффициенты общего уравнения прямой
// 	// Ax + By + C = 0
// 	double a = point2.y - point1.y;
// 	double b = point1.x - point2.x;
// 	double c = point2.x * point1.y - point1.x * point2.y;
//
// 	// по формуле расстояния от точки до прямой:
// 	double numerator = a * x + b * y + c;
// 	if (numerator < 0) {
// 		numerator *= -1;
// 	}
//
// 	double denominator = std::sqrt(a * a + b * b);
// 	return numerator / denominator;
// }

double Point::distanceToSegment(const Point& p1, const Point& p2) const {
	// Вектор отрезка
	double ax = p2.x - p1.x;
	double ay = p2.y - p1.y;
	double len2 = ax*ax + ay*ay;
	if (len2 < 1e-12) {
		// Отрезок вырожден в точку
		double dx = x - p1.x;
		double dy = y - p1.y;
		return std::sqrt(dx*dx + dy*dy);
	}

	// Проекция точки на прямую: t = ((p - p1)·(p2-p1)) / |p2-p1|^2
	double t = ((x - p1.x)*ax + (y - p1.y)*ay) / len2;

	if (t <= 0.0) {
		// Проекция за p1
		double dx = x - p1.x;
		double dy = y - p1.y;
		return std::sqrt(dx*dx + dy*dy);
	} else if (t >= 1.0) {
		// Проекция за p2
		double dx = x - p2.x;
		double dy = y - p2.y;
		return std::sqrt(dx*dx + dy*dy);
	} else {
		// Проекция внутри отрезка: расстояние до прямой
		double projx = p1.x + t*ax;
		double projy = p1.y + t*ay;
		double dx = x - projx;
		double dy = y - projy;
		return std::sqrt(dx*dx + dy*dy);
	}
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
