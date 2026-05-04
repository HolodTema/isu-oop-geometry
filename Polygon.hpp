#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include "Shape.hpp"
#include "Point.hpp"
#include "ArrayList.hpp"

class Polygon : public Shape {
public:

	explicit Polygon()
	{
		points_ = ArrayList<Point>();
	}

	explicit Polygon(std::istream& is) {
		size_t numberVertices;
		is >> numberVertices;
		points_ = ArrayList<Point>(numberVertices);
		Point point;
		for (size_t i = 0; i < numberVertices; ++i) {
			is >> point;
			addNextVertex(point);
		}
	}

	void addNextVertex(const Point& point) {
		points_.add(point);
	}

	Point* getPointsArray() const;

	double calcArea() const override;

	double calcPerimeter() const override;

	std::string name() const override;

private:
	ArrayList<Point> points_;
};

#endif
