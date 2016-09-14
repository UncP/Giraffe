CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O3 -fopenmp
LDFLAGS  = -lSDL -lSDLmain -lpng

DIR 		 = math utility object accelerator core
OBJ 		 = math/constant.o math/vector.o math/point.o math/ray.o math/vertex.o math/matrix.o \
					 utility/random.o utility/utility.o \
					 object/object.o object/sphere.o \
					 accelerator/bvh.o \
					 core/texture.o core/camera.o core/pathTracer.o core/scene.o core/window.o

Giraffe:$(OBJ) main/ray_tracer.cpp
	$(CPP) $(CPPFLAGS) -o Giraffe $(OBJ) main/ray_tracer.cpp $(LDFLAGS)

tag:
	ctags -R --sort=yes -f .tags

clean:
	for dir in $(DIR); do \
		(cd $$dir && rm *.o) || continue ; \
	done
	rm Giraffe *.png .tags
