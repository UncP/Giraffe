CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O3 -fopenmp
LDFLAGS  = -lpng

DIR 		 = math utility object accelerator core texture
OBJ 		 = math/constant.o math/vector.o math/point.o math/ray.o math/vertex.o math/matrix.o \
					 utility/random.o utility/intersection_info.o utility/utility.o \
					 object/object.o accelerator/bvh.o object/triangle.o object/sphere.o object/cube.o \
					 object/cylinder.o object/disk.o \
					 core/noise.o core/texture.o core/camera.o core/pathTracer.o core/scene.o \
					 core/window.o \
					 texture/brick.o texture/bump_brick.o texture/stripe.o texture/constant.o \
					 texture/noise.o texture/marble.o texture/image.o

Giraffe:$(OBJ) main/Giraffe.cpp
	$(CPP) $(CPPFLAGS) -o Giraffe $(OBJ) main/Giraffe.cpp $(LDFLAGS)

tag:
	ctags -R --sort=yes -f .tags

pic:
	rm *.png

clean:
	for dir in $(DIR); do \
		(cd $$dir && rm *.o) || continue ; \
	done
	rm Giraffe *.png .tags
