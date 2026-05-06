#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Polygon.hpp"
#include "shapeRecognition.hpp"

void testPolygon() {
	std::vector<Point> vecPoints = {Point(0,0), Point(3,0), Point(0,4)};
	Polygon polygonTriangle(vecPoints);
	std::cout << polygonTriangle.name() << " is triangle polygon\namount vertices: " << polygonTriangle.getNumberVertices()
			  << "\narea: " << polygonTriangle.calcArea() << "\nperimeter: " << polygonTriangle.calcPerimeter() << "\n\n";

	Point squarePoints[] = {Point(0,0), Point(2,0), Point(2,2), Point(0,2)};
	Polygon polygonSquare(4, squarePoints);
	std::cout << polygonSquare.name() << " is square polygon\namount vertices: " << polygonSquare.getNumberVertices()
			  << "\narea: " << polygonSquare.calcArea() << "\nperimeter: " << polygonSquare.calcPerimeter() << "\n\n";

	std::istringstream iss("5\n0 0\n2 0\n3 1\n1 3\n-1 2");
	Polygon polygonPentagon(iss);
	std::cout << polygonPentagon.name() << " is pentagon polygon\namount vertices: " << polygonPentagon.getNumberVertices()
			  << "\narea: " << polygonPentagon.calcArea() << "\nperimeter: " << polygonPentagon.calcPerimeter() << "\n\n";

	try {
		std::cout << "Expect catching std::invalid_argument exception:\n";
		std::vector<Point> badPoints = {Point(0,0), Point(1,0)};
		Polygon polygonBad(badPoints);
	} catch (const std::exception& e) {
		std::cout << e.what() << "\n";
		std::cout << "--------------------\n\n";
	}
}

void testPolygonFromFile() {
	const std::string FILE_PATH = "./assets/granitsy-uchastka.txt";
	std::ifstream ifs(FILE_PATH);

	if (!ifs.is_open()) {
		std::cout << "Error: unable to find file " << FILE_PATH << "\n";
		return;
	}

	Polygon polygon(ifs);
	ifs.close();
	if (ifs) {
		std::cout << "Polygon created from file successfully!\n";
		std::cout << "Number of vertices = " << polygon.getNumberVertices() << "\n";
		std::cout << "Polygon area = " << polygon.calcArea() << "\n";
	}
	else {
		std::cout << "Error: std::istream object set badbit or failbit during reading Polygon.\n";
	}
}

int main() {
	// testPolygonFromFile();
	// testPolygon();

	std::ifstream ifs("./assets/input1.dat");
	if (!ifs.is_open()) {
		std::cout << "Error: no file input1.dat.\n";
		return 1;
	}

	recognizeShapes(ifs, std::cout, 700, 700);
	return 0;
}
