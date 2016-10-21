CPP      = g++
CPPFLAGS = -std=c++14 -Wall -O3 -fopenmp
LDFLAGS  = -lpng

DIR      = math utility core accelerator object texture light
OBJ      = math/constant.o math/vector.o math/point.o math/ray.o math/vertex.o math/matrix.o \
           utility/random.o utility/intersection_info.o utility/utility.o \
           core/object.o core/noise.o core/texture.o core/light.o core/camera.o \
           core/pathTracer.o core/scene.o core/window.o \
           accelerator/bvh.o object/triangle.o object/sphere.o object/cube.o \
           object/cylinder.o object/disk.o \
           texture/brick.o texture/bump_brick.o texture/stripe.o texture/constant.o \
           texture/noise.o texture/marble.o texture/image.o \
           light/point.o light/directional.o light/area.o light/texture.o

Giraffe:$(OBJ) main/Giraffe.cpp
	$(CPP) $(CPPFLAGS) -o Giraffe $(OBJ) main/Giraffe.cpp $(LDFLAGS)

path:
	$(CPP) $(CPPFLAGS) -c core/pathTracer.cpp -DLIGHT
	mv pathTracer.o core

tag:
	ctags -R --sort=yes -f .tags

pic:
	rm *.png

clean:
	for dir in $(DIR); do \
		(cd $$dir && rm *.o) || continue ; \
	done
	rm Giraffe *.png .tags
