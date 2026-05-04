#include "Circle.hpp"

Point Circle::getCenter() const {
	return center_;
}

double Circle::getRadius() const {
	return radius_;
}

double Circle::calcArea() const {
	return PI * radius_ * radius_;
}

double Circle::calcPerimeter() const {
	return 2 * PI * radius_;
}

std::string Circle::name() const {
	return "Circle";
}
