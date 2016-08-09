###			https://www.github.com/UncP/Mini_Ray_Tracer			###

CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O3

all:pathTracer.o camera.o scene.o window.o

pathTracer.o:pathTracer.hpp pathTracer.cpp
camera.o:camera.hpp camera.cpp
scene.o:scene.hpp scene.cpp
window.o:window.hpp window.cpp
	$(CPP) $(CPPFLAGS) -c -fopenmp window.cpp

clean:
	rm *.o