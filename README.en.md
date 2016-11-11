##Giraffe Distributed Monte Carlo Ray Tracer
[中文版 README](./README.md)

###Giraffe is a Distributed Monte Carlo Ray Tracer which has its own ray tracing language, written in C++11/14

***

###Features
* Multi BRDF(reflect, refract, glossy, specular...)
* Anti-aliasing
* Global illumination
* Monte Carlo Integration
* Distributed Path Tracing
* Explicit Lighting
* Russian Roulette
* Procedural Texture(Brick, Stripe, Image, Grid, Spot)
* Bump Mapping
* Perlin Noise(Marble)
* Depth of field
* Sampler(Uniform, Stratified, Halton)
* Light(Point, Directional, Area, Texture)
* Object(Plane, Triangle, Sphere, Quad, Cylinder, Disk)
* Acceleration data structures
	- BVH
		+	AABB (Axis-Aligned Bounding Box)
		+	DOP	(Discrete Oriented Polytopes)
* Giraffe Ray Tracing Language


####Reflection & Refraction
![](./image/reflect_refract.png)

####Brick Texture
![](./image/brick.png)

####Depth of Field
![](./image/depth_of_field.png)

####Puppy
![](./image/puppy.png)

####Bear
![](./image/bear.png)

***If you are interested in Giraffe

`Enter src directory and make && ./Giraffe puppy 4(puppy is in directory scene, any file with suffix Giraffe is Ok, 4 means sample number, default is 1, you can change it to 8, 16...Also you need to have header file png.h and compiler that supports C++11/14, if not, change parameter 14 to 11 in Makefile)`
