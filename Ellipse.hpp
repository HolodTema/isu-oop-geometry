#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include <cmath>
#include <stdexcept>
#include "Shape.hpp"
#include "Point.hpp"

class Ellipse : public Shape {
public:
	Ellipse(const Point &center, double horizontalSemiAxis, double verticalSemiAxis) : center_(center) {
		if (horizontalSemiAxis <= 0) {
			throw std::invalid_argument("Error: horizontal semi-axis must be > 0.");
		}
		if (verticalSemiAxis <= 0) {
			throw std::invalid_argument("Error: vertical semi-axis must be > 0.");
		}
		horizontalSemiAxis_ = horizontalSemiAxis;
		verticalSemiAxis_ = verticalSemiAxis;
	}

	Point getCenter() const;

	double getHorizontalSemiAxis() const;

	double getVerticalSemiAxis() const;

	double calcArea() const override;

	double calcPerimeter() const override;

	std::string name() const override;

private:
	const double PI = std::acos(-1.0);

	Point center_;
	double horizontalSemiAxis_;
	double verticalSemiAxis_;
};

#endif
