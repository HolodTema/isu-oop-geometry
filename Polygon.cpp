#include "Polygon.hpp"

void Polygon::addVertexToEnd(const Point& point) {
	vecPoints_.push_back(point);
}

size_t Polygon::getNumberVertices() const {
	return vecPoints_.size();
}

double Polygon::calcArea() const {
	auto it = vecPoints_.begin();
	if (it == vecPoints_.end()) {
		return 0;
	}

	++it;
	double result = 0;
	for (; it != vecPoints_.end(); ++it) {
		Point currPoint = *it;
		Point prevPoint = *(it - 1);
		result += prevPoint.x * currPoint.y - currPoint.x * prevPoint.y;
	}

	Point endPoint = *(vecPoints_.end() - 1);
	Point startPoint = *(vecPoints_.begin());
	result += startPoint.x * endPoint.y - endPoint.x * startPoint.y;

	if (result < 0) {
		result *= -1;
	}
	result *= 0.5;
	return result;
}

double Polygon::calcPerimeter() const {
	auto it = vecPoints_.begin();
	if (it == vecPoints_.end()) {
		return 0;
	}

	++it;
	double result = 0;
	for (; it != vecPoints_.end(); ++it) {
		Point currPoint = *it;
		Point prevPoint = *(it - 1);
		result += prevPoint.distanceTo(currPoint);
	}

	Point endPoint = *(vecPoints_.end() - 1);
	Point startPoint = *(vecPoints_.begin());
	result += startPoint.distanceTo(endPoint);
	return result;
}

std::string Polygon::name() const {
	return "Polygon";
}
