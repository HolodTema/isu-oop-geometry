#include "Rectangle.hpp"

double Rectangle::getWidth() const {
	return width_;
}

double Rectangle::getHeight() const {
	return height_;
}

double Rectangle::calcArea() const {
	return width_ * height_;
}

double Rectangle::calcPerimeter() const {
	return 2 * width_ + 2 * height_;
}

std::string Rectangle::name() const {
	return "Rectangle";
}
