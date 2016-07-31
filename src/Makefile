CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O3 -fopenmp
LDFLAGS  = -lSDL -lSDLmain -lpng

OBJ = random.o vector.o matrix.o sphere.o camera.o ray.o window.o scene.o

ray_tracer:$(OBJ) ray_tracer.cpp
	$(CPP) $(CPPFLAGS) -o ray_tracer $(OBJ) ray_tracer.cpp $(LDFLAGS)

clean:
	rm *.o .tags* demo.ppm demo.png ray_tracer