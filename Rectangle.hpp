#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <stdexcept>
#include "Shape.hpp"
#include "Point.hpp"

class Rectangle : public Shape {
public:

	Rectangle(const Point& topLeftPoint, const Point& bottomRightPoint):
		topLeftPoint_(topLeftPoint),
		bottomRightPoint_(bottomRightPoint)
	{ }

	Rectangle(double width, double height) {
		if (width <= 0) {
			throw std::invalid_argument("Error: width must be > 0.");
		}
		if (height <= 0) {
			throw std::invalid_argument("Error: height must be > 0.");
		}
		topLeftPoint_ = Point(0, 0);
		bottomRightPoint_ = Point(width, height);
	}

	double getWidth() const;

	double getHeight() const;

	Point getTopLeftPoint() const;

	Point getBottomRightPoint() const;

	double calcArea() const override;

	double calcPerimeter() const override;

	std::string name() const override;

private:
	Point topLeftPoint_;
	Point bottomRightPoint_;;
};

#endif
