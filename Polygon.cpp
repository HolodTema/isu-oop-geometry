#include "Polygon.hpp"

void Polygon::addVertexToEnd(const Point& point) {
	vecPoints_.push_back(point);
}

size_t Polygon::getNumberVertices() const {
	return vecPoints_.size();
}

size_t Polygon::approximateVertices() {
	if (vecPoints_.size() < 3) return 0;

	std::vector<Point> vecSimplifiedVertices;
	size_t n = vecPoints_.size();

	for (size_t i = 0; i < n; ++i) {
		// используем остаток от делелния на длину, чтобы не заморачиваться с outOfBounds
		// и чтобы проверять тройки точек в начале и конце вектора.
		const Point& prev = vecPoints_[(i - 1 + n) % n];
		const Point& curr = vecPoints_[i];
		const Point& next = vecPoints_[(i + 1) % n];

		if (!prev.isOnStraightLineWith(curr, next)) {
			vecSimplifiedVertices.push_back(curr);
		}
	}

	// если апроксимация сделала многоугольник вырожденным - отменяем апроксимацию вообще.
	if (vecSimplifiedVertices.size() < 3) {
		return 0;
	}

	size_t amountRemovedVertices = vecPoints_.size() - vecSimplifiedVertices.size();
	// std::move() позволяет избежать лишнее перекопирование из vecSimplifiedVertices в vecPoints - вместо
	// этого сработает оператор перемещающего присваивания.
	vecPoints_ = std::move(vecSimplifiedVertices);
	return amountRemovedVertices;
}

std::vector<Point> Polygon::getVertices() const {
	return vecPoints_;
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
