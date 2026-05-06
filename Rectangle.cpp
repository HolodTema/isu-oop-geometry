#include "Rectangle.hpp"

double Rectangle::getWidth() const {
	return bottomRightPoint_.x - topLeftPoint_.x;
}

double Rectangle::getHeight() const {
	return bottomRightPoint_.y - topLeftPoint_.y;
}

Point Rectangle::getTopLeftPoint() const {
	return topLeftPoint_;
}

Point Rectangle::getBottomRightPoint() const {
	return bottomRightPoint_;
}

double Rectangle::calcArea() const {
	return getWidth() * getHeight();
}

double Rectangle::calcPerimeter() const {
	return 2 * getWidth() + 2 * getHeight();
}

std::string Rectangle::name() const {
	return "Rectangle";
}
