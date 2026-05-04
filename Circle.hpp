#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <cmath>
#include "Point.hpp"
#include "Shape.hpp"

class Circle : public Shape {
public:

	Circle(const Point& center, double radius):
		center_(center),
		radius_(radius) {
	}

	Point getCenter() const;

	double getRadius() const;

	double calcArea() const override;

	double calcPerimeter() const override;

	std::string name() const override;

private:
	const double PI = std::acos(-1.0);
	Point center_;
	double radius_;
};

#endif
