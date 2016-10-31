CPP      = g++
CPPFLAGS = -std=c++14 -Wall -O3 -fopenmp
LDFLAGS  = -lpng

DIR      = math utility core accelerator object texture light
OBJ      = math/constant.o math/vector.o math/point.o math/ray.o math/vertex.o math/matrix.o \
           utility/random.o utility/sampler.o utility/isect.o \
           utility/image_io.o \
           core/object.o core/noise.o core/texture.o core/material.o core/light.o core/camera.o \
           core/scene.o\
           accelerator/bvh.o \
           texture/brick.o texture/stripe.o texture/noise.o texture/marble.o texture/image.o \
           material/diffuse.o material/mirror.o material/glossy.o material/retro.o \
           material/halton.o \
           light/point.o light/directional.o light/area.o light/texture.o \
           object/plane.o object/sphere.o object/cylinder.o \
           core/path_tracer.o core/tl_parser.o
           # object/triangle.o object/cube.oobject/disk.o \

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
