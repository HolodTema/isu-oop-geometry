#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include "Shape.hpp"
#include "Point.hpp"

class Polygon : public Shape {
public:

	explicit Polygon(size_t numberVertices, Point* points):
		numberVertices_(numberVertices),
		points_(points)
	{ }

	explicit Polygon(std::istream& is) {
		is >> numberVertices_;
		points_ = new Point[numberVertices_];
		Point point;
		for (size_t i = 0; i < numberVertices_; ++i) {
			is >> point;
			points_[i] = point;
		}
	}

	~Polygon() override {
		delete[] points_;
	}

	size_t getNumberVertices() const;

	double calcArea() const override;

	double calcPerimeter() const override;

	std::string name() const override;

private:
	size_t numberVertices_;
	Point* points_;
};

#endif
