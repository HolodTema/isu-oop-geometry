#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"
#include "Point.hpp"

class Triangle : public Shape {
public:

	Triangle(const Point& first, const Point& second, const Point& third):
		firstPoint_(first),
		secondPoint_(second),
		thirdPoint_(third)
	{ }

	// point1 - point2
	double getFirstEdgeLen() const;

	// point2 - point3
	double getSecondEdgeLen() const;

	// point3 - point1
	double getThirdEdgeLen() const;

	double calcArea() const override;

	double calcPerimeter() const override;

	std::string name() const override;

private:
	Point firstPoint_;
	Point secondPoint_;
	Point thirdPoint_;
};

#endif
