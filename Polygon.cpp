#include "Polygon.hpp"

void Polygon::addVertexToEnd(const Point& point) {
	vecPoints_.push_back(point);
}

size_t Polygon::getNumberVertices() const {
	return vecPoints_.size();
}

size_t Polygon::approximateVertices() {
	size_t amountApproximatedVertices = 0;
	for (size_t i = 0; i < vecPoints_.size() - 2; ++i) {
		Point p1 = vecPoints_[i];
		Point p2 = vecPoints_[i+1];
		Point p3 = vecPoints_[i+2];
		if (p1.isOnStraightLineWith(p2, p3)) {
			vecPoints_.erase(vecPoints_.begin() + i + 1);
			i --;
			amountApproximatedVertices++;
		}
	}
	return amountApproximatedVertices;
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
