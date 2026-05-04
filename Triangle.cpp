#include "Triangle.hpp"

#include <cmath>

double Triangle::calcArea() const {
	double firstEdge = firstPoint_.distanceTo(secondPoint_);
	double secondEdge = secondPoint_.distanceTo(thirdPoint_);
	double thirdEdge = thirdPoint_.distanceTo(firstPoint_);

	double p = (firstEdge + secondEdge + thirdEdge) / 2.0;

	return std::sqrt(p * (p - firstEdge) * (p - secondEdge) * (p - thirdEdge));
}

double Triangle::calcPerimeter() const {
	double firstEdge = firstPoint_.distanceTo(secondPoint_);
	double secondEdge = secondPoint_.distanceTo(thirdPoint_);
	double thirdEdge = thirdPoint_.distanceTo(firstPoint_);

	return firstEdge + secondEdge + thirdEdge;
}

std::string Triangle::name() const {
	return "Triangle";
}
