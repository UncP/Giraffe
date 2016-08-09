###			https://www.github.com/UncP/Mini_Ray_Tracer			###

CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O3

all:constant.o vector.o point.o ray.o vertex.o matrix.o

constant.o:constant.hpp constant.cpp
point.o:point.hpp point.cpp
vector.o:vector.hpp vector.cpp
ray.o:ray.hpp ray.cpp
vertex.o:vertex.hpp vertex.cpp
matrix.o:matrix.hpp matrix.cpp

clean:
	rm *.o