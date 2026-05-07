#include "Polygon.hpp"

void Polygon::addVertexToEnd(const Point& point) {
	vecPoints_.push_back(point);
}

size_t Polygon::getNumberVertices() const {
	return vecPoints_.size();
}

size_t Polygon::approximateVertices(double accuracy) {
	if (vecPoints_.size() < 3) return 0;

	std::vector<Point> vecSimplifiedVertices;
	size_t n = vecPoints_.size();

	for (size_t i = 0; i < n; ++i) {
		// используем остаток от деления на длину, чтобы не заморачиваться с outOfBounds
		// и чтобы проверять тройки точек в начале и конце вектора.
		const Point& prev = vecPoints_[(i - 1 + n) % n];
		const Point& curr = vecPoints_[i];
		const Point& next = vecPoints_[(i + 1) % n];

		if (!prev.isOnStraightLineWith(curr, next, accuracy)) {
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

void Polygon::rdpRecursive(const std::vector<Point>& vecVertices, size_t first, size_t last, double accuracy, std::vector<bool>& vecNeedKeepVertex) {
	if (last - first <= 1) {
		return;
	}

	double maxDistance = -1.0;
	size_t index = first;

	for (size_t i = first + 1; i < last; ++i) {
		double distance = vecVertices[i].distanceToSegment(vecVertices[first], vecVertices[last]);
		if (distance > maxDistance) {
			maxDistance = distance;
			index = i;
		}
	}
	if (maxDistance > accuracy) {
		vecNeedKeepVertex[index] = true;
		rdpRecursive(vecVertices, first, index, accuracy, vecNeedKeepVertex);
		rdpRecursive(vecVertices, index, last, accuracy, vecNeedKeepVertex);
	}
}

size_t Polygon::approximateVerticesRDP(double accuracy) {
	// если уже 3 вершины, то апроксимировать нечего
	if (vecPoints_.size() <= 3) {
		return 0;
	}

	std::vector<Point> vecVertices = vecPoints_;
	// добавляем первую точку контура в конец, чтобы обработать startPoint-endPoint ребро
	vecVertices.push_back(vecPoints_.front());

	std::vector<bool> vecNeedKeepVertex(vecVertices.size(), false);
	vecNeedKeepVertex.front() = true;
	vecNeedKeepVertex.back() = true;

	rdpRecursive(vecVertices, 0, vecVertices.size() - 1, accuracy, vecNeedKeepVertex);

	std::vector<Point> vecResultVertices;
	for (size_t i = 0; i < vecVertices.size(); ++i) {
		if (vecNeedKeepVertex[i]) {
			vecResultVertices.push_back(vecVertices[i]);
		}
	}

	// если первая и последняя вершина совпали, удалим дубликат вершины
	if (vecResultVertices.size() > 1 && vecResultVertices.front() == vecResultVertices.back()) {
		vecResultVertices.pop_back();
	}
	size_t amountDeletedVertices = vecPoints_.size() - vecResultVertices.size();
	vecPoints_ = std::move(vecResultVertices);
	return amountDeletedVertices;
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
