#ifndef SHAPE_RECOGNIZER_HPP
#define SHAPE_RECOGNIZER_HPP

#include <iostream>
#include <vector>
#include "Point.hpp"
#include "Polygon.hpp"

class ShapeRecognizer {
public:
	//итерируемся по полю и если находим единицу
	//рекурсивно получаем контур фигуры
	//далее проводим апроксимацию контура - то есть
	//создаем из контура полигон
	//смотрим пропорциональность координат соседних вершин
	//что 3 точки соседних на одной прямой - тогда одну
	//точку убираем и тд
	//и если у многоугольника останется 4 вершины - это

	void recognize(std::istream& is, size_t width, size_t height) {
		this->width = width;
		this->height = height;
		allPoints_ = new bool[width * height];
		int pointValue = 0;
		for (size_t i = 0; i < width * height; i++) {
			is >> pointValue;
			allPoints_[i] = pointValue == 1;
		}

		std::vector<Point> vecVisited;
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				Point point(x, y);
				if (isPointInContour(x, y) && !isPointVisited(vecVisited, point)) {
					std::vector<Point> vecContour;
					findShapeContourRecursive(vecContour, vecVisited, point);
					Polygon polygon()
				}
			}
		}
	}

	void findShapeContourRecursive(std::vector<Point>& vecContour, std::vector<Point>& vecVisited, const Point& point) {
		if (allPoints_[y * width + x] && !isPointVisited(vecVisited, point)) {
			vecVisited.push_back(point);
			if (isPointInContour(x, y)) {
				vecContour.push_back(point);
			}
			if (x > 0) {
				findShapeContourRecursive(vecContour, vecVisited, x - 1, y);
			}
			if (y > 0) {
				findShapeContourRecursive(vecContour, vecVisited, x, y - 1);
			}
			if (x < width - 1) {
				findShapeContourRecursive(vecContour, vecVisited, x + 1, y);
			}
			if (y < height - 1) {
				findShapeContourRecursive(vecContour, vecVisited, x, y + 1);
			}
		}
	}

	bool isPointInContour(int x, int y) {
		if (!allPoints_[y * width + x]) {
			return false;
		}
		bool hasRightNeighbour = (x - 1 >= 0) && allPoints_[y * width + x - 1];
		bool hasLeftNeighbour = (x + 1 < width) && allPoints_[y * width + x + 1];
		bool hasTopNeighbour = (y - 1 >= 0) && allPoints_[(y - 1) * width + x];
		bool hasBottomNeighbour = (y + 1 < height) && allPoints_[(y + 1) * width + x];

		return (hasBottomNeighbour && hasLeftNeighbour) ||
			(hasBottomNeighbour && hasRightNeighbour) ||
			(hasLeftNeighbour && hasTopNeighbour) ||
			(hasRightNeighbour && hasTopNeighbour);
	}

	bool isPointVisited(std::vector<Point>& vecVisited, const Point& point) {
		for (std::vector<Point>::iterator it = vecVisited.begin(); it != vecVisited.end(); ++it) {
			if ((*it) == point) {
				return true;
			}
		}
		return false;
	}
private:
	size_t width = 0;
	size_t height = 0;
	bool* allPoints_ = nullptr;
	Point* visitedPoints_ = nullptr;


};

#endif
