#include "shapeRecognition.hpp"
#include <unordered_set>
#include "Polygon.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"

bool isPointInContour(size_t width, size_t height, const std::vector<bool>& allPoints, const Point& point) {
	int x = static_cast<int>(point.x);
	int y = static_cast<int>(point.y);

	if (x < 0 || x >= width || y < 0 || y >= height) {
		return false;
	}
	if (!allPoints[y * width + x]) {
		return false;
	}
	bool rightEmpty = (x - 1 < 0) || !allPoints[y * width + x - 1];
	bool leftEmpty = (x + 1 >= width) || !allPoints[y * width + x + 1];
	bool topEmpty = (y - 1 < 0) || !allPoints[(y - 1) * width + x];
	bool bottomEmpty = (y + 1 >= height) || !allPoints[(y + 1) * width + x];
	return rightEmpty || leftEmpty || topEmpty || bottomEmpty;
}

std::vector<Point> findShapeContour(
	size_t width,
	size_t height,
	const std::vector<bool>& allPoints,
	const Point& pointStart)
{
	// если стартовая точка не является контурной, то зачем мы вообще вызвали эту
	// функцию? Выходим.
	if (!isPointInContour(width, height, allPoints, pointStart)) {
		return std::vector<Point>();
	}

	// 8 направлений по индексам. Начиная от right, заканчивая topRight
	// то есть по часовой стрелке.
	int xDirections[8] = {1, 1, 0, -1, -1, -1,  0,  1};
	int yDirections[8] = {0, 1, 1,  1,  0, -1, -1, -1};

	int currX = static_cast<int>(pointStart.x);
	int currY = static_cast<int>(pointStart.y);

	// индекс первого направления, где есть контур по часовой стрелке.
	int firstClockwiseDir = -1;
	for (int dirIndex = 0; dirIndex < 8; dirIndex++) {
		int x = currX + xDirections[dirIndex];
		int y = currY + yDirections[dirIndex];
		if (isPointInContour(width, height, allPoints, Point(x, y))) {
			firstClockwiseDir = dirIndex;
			break;
		}
	}

	// если такого направления по часовой стрелке не нашлось, то мы
	// имеем дело с одинокой точкой - это не фигура
	if (firstClockwiseDir == -1) {
		return std::vector<Point>();
	}

	std::vector<Point> vecContour;
	vecContour.push_back(pointStart);

	// переходим к найденной нами ранее соседней контурной точке
	currX += xDirections[firstClockwiseDir];
	currY += yDirections[firstClockwiseDir];

	// prevDirection - какое направление было в прошлый раз
	int prevDirection = firstClockwiseDir;
	// directionToBackToPrevPoint - направление, чтобы вернуться в предыдущую точку.
	int directionToBackToPrevPoint = (firstClockwiseDir + 4) % 8;

	// итерируемся, пока не вернулись в начальную точку (пока не замкнули контур)
	// при этом помехи (линии небольшой толщины и тд) могут поломать алгоритм жука,
	// поэтому ставится ограничение итераций
	const size_t MAX_ITERATIONS = width*height;
	size_t amountIterations = 0;
	while (currX != pointStart.x || currY != pointStart.y) {
		if (amountIterations > MAX_ITERATIONS) {
			return std::vector<Point>();
		}
		vecContour.push_back(Point(currX, currY));

		// ищем следующую контурную точку по часовой стрелке от предыдущего направления
		int nextDirection = -1;
		for (int i = 0; i < 8; ++i) {
			int dir = (prevDirection + 7 + i) % 8;
			if (dir == directionToBackToPrevPoint) {
				continue;
			}
			int x = currX + xDirections[dir];
			int y = currY + yDirections[dir];
			if (isPointInContour(width, height, allPoints, Point(x, y))) {
				nextDirection = dir;
				break;
			}
		}

		// если новая контурная точка не нашлась - текущая точка тупиковая, контур окончен
		if (nextDirection == -1) {
			break;
		}

		// переходим к новой найденной точке, снова запоминаем направление к предыдущей точке
		currX += xDirections[nextDirection];
		currY += yDirections[nextDirection];
		prevDirection = nextDirection;
		directionToBackToPrevPoint = (nextDirection + 4) % 8;
		amountIterations++;
	}

	// стартовая точка может быть продублирована в начале и в конце вектоа
	// удаляем возможный дубликат
	if (!vecContour.empty() && vecContour.back() == pointStart) {
		vecContour.pop_back();
	}

	return vecContour;
}

void recognizeShapes(std::istream &is, std::ostream &os, size_t width, size_t height) {
	size_t amountRectangles = 0;
	size_t amountTriangles = 0;
	size_t amountEllipses = 0;

	std::vector<bool> allPoints;
	allPoints.resize(width * height);
	size_t i = 0;
	char ch;
	while (i < width * height && is.get(ch)) {
		if (ch == '0' || ch == '1') {
			allPoints[i] = ch == '1';
			++i;
		}
	}
	if (i != width * height) {
		os << "Error: invalid width or height - not all the data was read.\n";
		return;
	}

	std::unordered_set<Point, PointHash> setVisitedPoints;

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			Point point(x, y);
			if (isPointInContour(width, height, allPoints, point) && setVisitedPoints.find(point) == setVisitedPoints.end()) {
				std::vector<Point> vecContour = findShapeContour(width, height, allPoints, point);
				if (vecContour.size() < 3) {
					continue;
				}

				for (auto it = vecContour.begin(); it != vecContour.end(); ++it) {
					setVisitedPoints.insert(*it);
				}

				Polygon polygon(vecContour);
				os << polygon.approximateVerticesRDP(1) << "\n";
				size_t amountVertices = polygon.getNumberVertices();

				for (Point p : polygon.getVertices()) {
					os << p << " ";
				}
				os << "\n\n";

				if (amountVertices > 4) {
					amountEllipses++;
				}
				else if (amountVertices == 4) {
					// надо отсеять прямоугольники, высота или ширина которых = 2.
					// так как они являются частью линий-помех толщиной 1-2
					std::vector<Point> rectVertices = polygon.getVertices();
					bool isOrtogonalEdge01 = rectVertices[0].x == rectVertices[1].x || rectVertices[0].y == rectVertices[1].y;
					bool isOrtogonalEdge12 = rectVertices[1].x == rectVertices[2].x || rectVertices[1].y == rectVertices[2].y;
					bool isOrtogonalEdge23 = rectVertices[2].x == rectVertices[3].x || rectVertices[2].y == rectVertices[3].y;
					bool isOrtogonalEdge30 = rectVertices[3].x == rectVertices[0].x || rectVertices[3].y == rectVertices[0].y;
					if (isOrtogonalEdge01 && isOrtogonalEdge12 && isOrtogonalEdge23 && isOrtogonalEdge30) {
						Rectangle rectangle(rectVertices[0], rectVertices[2]);
						if (rectangle.getHeight() > 2 && rectangle.getWidth() > 2) {
							os << "Rectangle:\n";
							for (Point p : rectVertices) {
								os << p << " ";
							}
							os << "\n\n";
							amountRectangles++;
						}
					}
				}
				else if (amountVertices == 3) {
					std::vector<Point> triangleVertices = polygon.getVertices();
					Triangle triangle(triangleVertices[0], triangleVertices[1], triangleVertices[2]);
					if (triangle.getFirstEdgeLen() >= 6 && triangle.getSecondEdgeLen() >= 6 && triangle.getThirdEdgeLen() >= 6) {
						amountTriangles++;
					}
				}
			}
		}
	}
	os << "Ellipses = " << amountEllipses << "\n";
	os << "Rectangles = " << amountRectangles << "\n";
	os << "Triangles = " << amountTriangles << "\n";
}
