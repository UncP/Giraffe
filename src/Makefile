CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O3 -fopenmp
LDFLAGS  = -lSDL -lSDLmain

OBJ = vector.o sphere.o camera.o ray.o window.o

ray_tracer:$(OBJ) ray_tracer.cpp
	$(CPP) $(CPPFLAGS) -o ray_tracer $(OBJ) ray_tracer.cpp $(LDFLAGS)

clean:
	rm *.o .tags* *.ppm ray_tracer