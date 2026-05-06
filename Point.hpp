#ifndef POINT_HPP
#define POINT_HPP

#include <iosfwd>

struct Point {

	Point():
		x(0),
		y(0)
	{ }

	Point(double x, double y):
		x(x),
		y(y)
	{ }

	double distanceTo(const Point& other) const;

	bool isOnStraightLineWith(const Point& point2, const Point& point3) const;

	bool operator==(const Point& other) const;

	double x;
	double y;
};

struct PointHash {
	size_t operator()(const Point& point) const;
};

std::istream& operator>>(std::istream& is, Point& point);

std::ostream& operator<<(std::ostream& os, const Point& point);

#endif
