###			https://www.github.com/UncP/Mini_Ray_Tracer			###

CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O3 -fopenmp
# LDFLAGS  = -lSDL -lSDLmain -lpng
LDFLAGS  = -lpng
AC 			 =

OBJ = random.o vector.o vertex.o matrix.o mesh.o ray.o object.o bvh.o sphere.o \
			camera.o scene.o pathTracer.o window.o

ray_tracer:$(OBJ) ray_tracer.cpp
	$(CPP) $(CPPFLAGS) $(AC) -o ray_tracer $(OBJ) ray_tracer.cpp $(LDFLAGS)

ray.o:ray.cpp ray.hpp
	$(CPP) $(CPPFLAGS) -c $(AC) ray.cpp

clean:
	rm *.o .tags* *.png ray_tracer