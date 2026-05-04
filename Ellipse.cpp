#include "Ellipse.hpp"

Point Ellipse::getCenter() const {
	return center_;
}

double Ellipse::getHorizontalSemiAxis() const {
	return horizontalSemiAxis_;
}

double Ellipse::getVerticalSemiAxis() const {
	return verticalSemiAxis_;
}

double Ellipse::calcArea() const {
	return PI * horizontalSemiAxis_ * verticalSemiAxis_;
}

double Ellipse::calcPerimeter() const {
	double numerator = PI * horizontalSemiAxis_ * verticalSemiAxis_
		+ (horizontalSemiAxis_ - verticalSemiAxis_) * (horizontalSemiAxis_ - verticalSemiAxis_);
	double denominator = 0.25 * (horizontalSemiAxis_ + verticalSemiAxis_);
	return numerator / denominator;
}

std::string Ellipse::name() const {
	return "Ellipse";
}
