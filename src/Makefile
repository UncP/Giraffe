CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O3 -fopenmp
LDFLAGS  = -lSDL -lSDLmain -lpng

ray_tracer:vector.cpp ray.cpp ray_tracer.cpp
	$(CPP) $(CPPFLAGS) -o ray_tracer vector.cpp utility.cpp ray.cpp \
	ray_tracer.cpp $(LDFLAGS)

clean:
	rm ray_tracer .tags*