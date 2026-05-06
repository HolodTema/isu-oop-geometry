#include <iostream>
#include <fstream>
#include <string>
#include "Polygon.hpp"

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
	testPolygonFromFile();
	return 0;
}
