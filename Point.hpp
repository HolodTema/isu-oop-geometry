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

	double distanceToSegment(const Point& point1, const Point& point2) const;

	bool isOnStraightLineWith(const Point& point2, const Point& point3) const;

	bool isOnStraightLineWith(const Point& point2, const Point& point3, double accuracy) const;

	bool isOnStraightLineViaAngle(const Point& point2, const Point& point3, int minAngle) const {
		double xVector12 = point2.x - x;
		double yVector12 = point2.y - y;
		double lenVector12 = this->distanceTo(point2);

		double xVector23 = point3.x - point2.x;
		double yVector23 = point3.y - point2.y;
		double lenVector23 = point2.distanceTo(point3);

		double vectorMultiply = xVector12 * xVector23 + yVector12 * yVector23;
		double sin = vectorMultiply / (lenVector23 * lenVector12);


	}

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
