# C++ compiler
CXX = g++


# compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11 -O2


# target file - the file of our program
TARGET = main


# source c++ files
SOURCES = main.cpp Point.cpp Circle.cpp Ellipse.cpp Rectangle.cpp Triangle.cpp Polygon.cpp shapeRecognition.cpp


# default makefile rule
all: 
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)


# if we clean project, we delete all the .o files and executable-file
clean:
	rm -f $(TARGET)


# .PHONY means that these targets are not files
.PHONY: all clean

