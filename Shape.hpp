#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>

class Shape {
public:

	virtual ~Shape() {

	}

	virtual double calcArea() const = 0;

	virtual double calcPerimeter() const = 0;

	virtual std::string name() const = 0;
};

#endif
