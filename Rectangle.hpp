#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

class Rectangle : public Shape{
public:

	Rectangle(double width, double height):
		width_(width),
		height_(height)
	{ }

	double getWidth() const;

	double getHeight() const;

	double calcArea() const override;

	double calcPerimeter() const override;

	std::string name() const override;

private:
	double width_;
	double height_;
};

#endif
