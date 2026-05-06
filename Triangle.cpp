#include "Triangle.hpp"

#include <cmath>

// point1 - point2
double Triangle::getFirstEdgeLen() const {
	return firstPoint_.distanceTo(secondPoint_);
}

// point2 - point3
double Triangle::getSecondEdgeLen() const {
	return secondPoint_.distanceTo(thirdPoint_);
}

// point3 - point1
double Triangle::getThirdEdgeLen() const {
	return thirdPoint_.distanceTo(firstPoint_);
}

double Triangle::calcArea() const {
	double firstEdge = getFirstEdgeLen();
	double secondEdge = getSecondEdgeLen();
	double thirdEdge = getThirdEdgeLen();

	double p = (firstEdge + secondEdge + thirdEdge) / 2.0;

	return std::sqrt(p * (p - firstEdge) * (p - secondEdge) * (p - thirdEdge));
}

double Triangle::calcPerimeter() const {
	double firstEdge = getFirstEdgeLen();
	double secondEdge = getSecondEdgeLen();
	double thirdEdge = getThirdEdgeLen();
	return firstEdge + secondEdge + thirdEdge;
}

std::string Triangle::name() const {
	return "Triangle";
}
