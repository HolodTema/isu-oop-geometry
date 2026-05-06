#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>
#include "Shape.hpp"
#include "Point.hpp"

class Polygon : public Shape {
public:

	explicit Polygon(const std::vector<Point>& vecPoints) {
		if (vecPoints.size() < 3) {
			throw std::invalid_argument("Error: polygon must have at least 3 vertices.");
		}
		vecPoints_ = vecPoints;
	}

	explicit Polygon(size_t numberVertices, Point* points)
	{
		if (numberVertices < 3) {
			throw std::invalid_argument("Error: polygon must have at least 3 vertices.");
		}
		vecPoints_.reserve(numberVertices);
		for (size_t i = 0; i < numberVertices; i++) {
			vecPoints_.push_back(points[i]);
		}
	}

	explicit Polygon(std::istream& is) {
		size_t amountPoints;
		is >> amountPoints;
		if (amountPoints < 3) {
			throw std::invalid_argument("Error: polygon must have at least 3 vertices.");
		}
		vecPoints_.reserve(amountPoints);
		Point point;
		for (size_t i = 0; i < amountPoints; ++i) {
			is >> point;
			vecPoints_.push_back(point);
		}
	}

	void addVertexToEnd(const Point& point);

	size_t getNumberVertices() const;

	double calcArea() const override;

	double calcPerimeter() const override;

	std::string name() const override;

private:
	std::vector<Point> vecPoints_;

};

#endif
