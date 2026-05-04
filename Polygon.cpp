#include "Polygon.hpp"


size_t Polygon::getNumberVertices() const {
	return numberVertices_;
}


double Polygon::calcArea() const {
	double result = 0;
	for (size_t i = 0; i < numberVertices_ - 1; ++i) {
		result += points_[i].x * points_[i+1].y - points_[i+1].x * points_[i].y;
	}
	result += points_[numberVertices_ - 1].x * points_[0].y - points_[0].x * points_[numberVertices_ - 1].y;

	if (result < 0) {
		result *= -1;
	}
	result *= 0.5;
	return result;
}

double Polygon::calcPerimeter() const {
	double result = 0;
	for (size_t i = 0; i < numberVertices_ - 1; ++i) {
		result += points_[i].distanceTo(points_[i+1]);
	}
	result += points_[0].distanceTo(points_[numberVertices_ - 1]);
	return result;
}

std::string Polygon::name() const {
	return "Polygon";
}
