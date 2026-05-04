#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>

class Shape {
public:

	virtual ~Shape() {

	}

	virtual double calcArea() const = 0;

	virtual double calcPerimeter() const = 0;

	virtual char* name() const = 0;

private:
	std::string name_;

};

#endif
