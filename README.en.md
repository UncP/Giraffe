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
* Procedural Texture(Brick, Stripe, Image, Grid)
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

***

`If you are interested, enter src directory and make && ./Giraffe`
