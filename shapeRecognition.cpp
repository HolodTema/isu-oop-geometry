#include "shapeRecognition.hpp"
#include "Polygon.hpp"

bool isPointInContour(size_t width, size_t height, const std::vector<bool>& allPoints, const Point& point) {
	int x = static_cast<int>(point.x);
	int y = static_cast<int>(point.y);
	if (!allPoints[y * width + x]) {
		return false;
	}
	bool hasRightNeighbour = (x - 1 >= 0) && allPoints[y * width + x - 1];
	bool hasLeftNeighbour = (x + 1 < width) && allPoints[y * width + x + 1];
	bool hasTopNeighbour = (y - 1 >= 0) && allPoints[(y - 1) * width + x];
	bool hasBottomNeighbour = (y + 1 < height) && allPoints[(y + 1) * width + x];
	if (hasBottomNeighbour && hasLeftNeighbour && hasTopNeighbour && hasRightNeighbour) {
		return false;
	}
	return (hasBottomNeighbour && hasLeftNeighbour) ||
		   (hasBottomNeighbour && hasRightNeighbour) ||
		   (hasLeftNeighbour && hasTopNeighbour) ||
		   (hasRightNeighbour && hasTopNeighbour);
}

void findShapeContourRecursive(
	size_t width,
	size_t height,
	const std::vector<bool> &allPoints,
	std::vector<Point> &vecContour,
	std::unordered_set<Point, PointHash> &setVisitedPoints,
	const Point &point
) {
	int x = point.x;
	int y = point.y;

	if (setVisitedPoints.find(point) != setVisitedPoints.end()) {
		return;
	}

	vecContour.push_back(point);
	setVisitedPoints.insert(point);

	if (x + 1 < width) {
		Point pointRight = Point(x + 1, y);
		if (isPointInContour(width, height, allPoints, pointRight)) {
			if (setVisitedPoints.find(pointRight) == setVisitedPoints.end()) {
				findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointRight);
				return;
			}
		}

	}
	if (x - 1 >= 0) {
		Point pointLeft = Point(x - 1, y);
		if (isPointInContour(width, height, allPoints, pointLeft)) {
			if (setVisitedPoints.find(pointLeft) == setVisitedPoints.end()) {
				findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointLeft);
				return;
			}
		}
	}
	if (y - 1 >= 0) {
		Point pointTop = Point(x, y - 1);
		if (isPointInContour(width, height, allPoints, pointTop)) {
			if (setVisitedPoints.find(pointTop) == setVisitedPoints.end()) {
				findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointTop);
				return;
			}
		}
	}
	if (y + 1 < height) {
		Point pointBottom = Point(x, y + 1);
		if (isPointInContour(width, height, allPoints, pointBottom)) {
			if (setVisitedPoints.find(pointBottom) == setVisitedPoints.end()) {
				findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointBottom);
				return;
			}
		}
	}
	if (x - 1 >= 0 && y - 1 >= 0) {
		Point pointTopLeft = Point(x - 1, y - 1);
		if (isPointInContour(width, height, allPoints, pointTopLeft)) {
			if (setVisitedPoints.find(pointTopLeft) == setVisitedPoints.end()) {
				findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointTopLeft);
				return;
			}
		}
	}
	if (x - 1 >= 0 && y + 1 < height) {
		Point pointBottomLeft = Point(x - 1, y + 1);
		if (isPointInContour(width, height, allPoints, pointBottomLeft)) {
			if (setVisitedPoints.find(pointBottomLeft) == setVisitedPoints.end()) {
				findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointBottomLeft);
				return;
			}
		}
	}
	if (x + 1 < width && y - 1 >= 0) {
		Point pointTopRight = Point(x + 1, y - 1);
		if (isPointInContour(width, height, allPoints, pointTopRight)) {
			if (setVisitedPoints.find(pointTopRight) == setVisitedPoints.end()) {
				findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointTopRight);
				return;
			}
		}
	}
	if (x + 1 < width && y + 1 < height) {
		Point pointBottomRight = Point(x + 1, y + 1);
		if (isPointInContour(width, height, allPoints, pointBottomRight)) {
			if (setVisitedPoints.find(pointBottomRight) == setVisitedPoints.end()) {
				findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, pointBottomRight);
				return;
			}
		}
	}
}

void recognizeShapes(std::istream &is, std::ostream &os, size_t width, size_t height) {
	size_t amountSquares = 0;
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

	std::unordered_set<Point, PointHash> setVisitedPoints(width * height);

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			Point point = Point(x, y);
			std::vector<Point> vecContour;
			if (isPointInContour(width, height, allPoints, point)) {
				if (setVisitedPoints.find(point) == setVisitedPoints.end()) {
					findShapeContourRecursive(width, height, allPoints, vecContour, setVisitedPoints, point);
					os << "after finding amount vertices = " << vecContour.size() << "\n";
					for (Point p : vecContour) {
						os << p << " ";
					}
					os << "\n";
					if (vecContour.size() < 3) {
						os << "Cannot create polygon from < 3 vertices. Skip this figure.\n";
						continue;
					}
					Polygon polygon(vecContour);

					size_t verticesOptimized = polygon.approximateVertices();
					if (polygon.getNumberVertices() > 4) {
						amountEllipses++;
					}
					if (polygon.getNumberVertices() == 4) {
						amountSquares++;
					}
					if (polygon.getNumberVertices() == 3) {
						amountTriangles++;
					}
					os << "optimized: " << verticesOptimized << "\n";
					os << "vertices left " << polygon.getNumberVertices() << "\n";
					os << "------------------\n\n";
				}
			}
		}
	}
	os << "Ellipses = " << amountEllipses << "\n";
	os << "Squares = " << amountSquares << "\n";
	os << "Triangles = " << amountTriangles << "\n";
}
