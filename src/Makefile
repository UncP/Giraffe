CXX      = g++
CPPFLAGS = -std=c++14 -Wall -O3 -fopenmp
LDFLAGS  = -lpng

DIR      = math utility core accelerator sampler object texture light
OBJ      = math/constant.o math/vector.o math/point.o math/ray.o math/vertex.o math/matrix.o \
           utility/random.o utility/isect.o \
           utility/image_io.o utility/slice.o \
           core/object.o core/noise.o core/texture.o core/sampler.o core/material.o \
           core/light.o core/camera.o core/scene.o \
           accelerator/box.o accelerator/bvh.o \
           sampler/uniform.o sampler/stratified.o sampler/halton.o \
           texture/constant.o texture/brick.o texture/stripe.o texture/grid.o texture/noise.o \
           texture/marble.o texture/image.o texture/bump_brick.o texture/spot.o \
           texture/cellular.o \
           light/point.o light/directional.o light/area.o light/texture.o \
           object/plane.o object/sphere.o object/cylinder.o object/cone.o \
           core/path_tracer.o core/tl_parser.o
           # material/diffuse.o material/mirror.o material/glossy.o material/retro.o \
           # object/triangle.o object/cube.oobject/disk.o \

Giraffe:$(OBJ) main/Giraffe.cpp
	$(CXX) $(CPPFLAGS) -o Giraffe $(OBJ) main/Giraffe.cpp $(LDFLAGS)

tag:
	ctags -R --sort=yes -f .tags

pic:
	rm *.png

clean:
	for dir in $(DIR); do \
		(cd $$dir && rm *.o) || continue ; \
	done
	rm Giraffe *.png .tags
