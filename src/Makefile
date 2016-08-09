###			https://www.github.com/UncP/Mini_Ray_Tracer			###

CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O3 -fopenmp -o
LDFLAGS  = -lSDL -lSDLmain -lpng

DIR 		 = math utility object accelerator core
OBJ 		 = math/constant.o math/vector.o math/point.o math/ray.o math/vertex.o math/matrix.o \
					 utility/random.o utility/utility.o \
					 object/object.o object/sphere.o object/mesh.o \
					 accelerator/bvh.o \
					 core/camera.o core/pathTracer.o core/scene.o core/window.o

all:module ray_tracer

ray_tracer:$(OBJ) main/ray_tracer.cpp
	$(CPP) $(CPPFLAGS) ray_tracer $(OBJ) main/ray_tracer.cpp $(LDFLAGS)

module:
	for dir in $(DIR); do \
		(cd $$dir && make && cd ..) || exit ; \
	done

tag:
	ctags -R --sort=yes -f .tags

clean:
	for dir in $(DIR); do \
		(cd $$dir && make clean) || continue ; \
	done
	rm ray_tracer *.png .tags
