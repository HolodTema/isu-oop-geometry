#include "Point.hpp"
#include <iostream>
#include <functional>
#include <cmath>

double Point::distanceTo(const Point& other) const {
	double distanceX = x - other.x;
	double distanceY = y - other.y;
	return std::sqrt(distanceX * distanceX + distanceY * distanceY);
}

double Point::distanceToSegment(const Point& point1, const Point& point2) const {
	// вектор из отрезка
	double aX = point2.x - point1.x;
	double aY = point2.y - point1.y;
	double aLen = std::sqrt(aX * aX + aY * aY);
	if (aLen < 1) {
		// если отрезок является точкой, то считаем расстояние до точки.
		return distanceTo(point1);
	}

    // вектор от одного из концов отрезка до точки вне отрезка
    double pX = x - point1.x;
    double pY = y - point1.y;
    double pLen = std::sqrt(pX * pX + pY * pY);

    // косинус находится исходя из скалярного произведения векторов
    double cos = (pX * aX + pY * aY) / (pLen * aLen);

    if (cos < 0) {
        double distance1 = distanceTo(point1);
        double distance2 = distanceTo(point2);
        if (distance1 < distance2) {
            return distance1;
        }
        return distance2;
    }

    // находим коэффициенты общего уравнения прямой
 	// Ax + By + C = 0
 	double a = point2.y - point1.y;
 	double b = point1.x - point2.x;
 	double c = point2.x * point1.y - point1.x * point2.y;

 	// по формуле расстояния от точки до прямой:
 	double numerator = a * x + b * y + c;
 	if (numerator < 0) {
 		numerator *= -1;
 	}

 	double denominator = std::sqrt(a * a + b * b);
 	return numerator / denominator;
}

bool Point::isOnStraightLineWith(const Point& point2, const Point& point3) const {
	// векторное произведение векторов в координатах
	return (point2.y - y) * (point3.x - point2.x) == (point3.y - point2.y) * (point2.x - x);
}

bool Point::isOnStraightLineWith(const Point& point2, const Point& point3, double accuracy) const {
	// векторное произведение векторов в координатах
	double vectorMultiply = (point2.x - x) * (point3.y - point2.y) - (point3.x - point2.x) * (point2.y - y);
	if (vectorMultiply < 0) {
		vectorMultiply *= -1;
	}
	return vectorMultiply <= accuracy;
}

bool Point::operator==(const Point& other) const {
	return x == other.x && y == other.y;
}

std::istream& operator>>(std::istream& is, Point& point) {
	std::istream::sentry s(is);
	if (!s) {
		return is;
	}
	is >> point.x;
	is >> point.y;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
	std::ostream::sentry s(os);
	if (!s) {
		return os;
	}
	os << "(" << point.x << ", " << point.y << ")";
	return os;
}

size_t PointHash::operator()(const Point& point) const {
	size_t hashX = std::hash<double>{}(point.x);
	size_t hashY = std::hash<double>{}(point.y);
	return hashX ^ (hashY * 0x9e3779b9 + (hashX << 6) + (hashX >> 2));
    // хеширование выше лучше, чем хеширование в комментарии, ибо меньше коллизий.
    // 0x9e3779b9 - число Фи - золотое сечение
    // сдвиги на 6 и на 2 влево и вправо подобраны просто так, их можно поменять.
    //
    // но если делать такое хеширование, то тоже все будет работать, просто будет немного больше коллизий
	// return hashX ^ (hashY << 1);
}
