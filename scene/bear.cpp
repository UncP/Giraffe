/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-10-22 12:29:29
**/

int screenWidth = 512, screenHeight = 512;

Camera *camera = new PerspectiveCamera(	Point3d(0, 0, 0), 	\
																				Vector3d(0, 0, -1.0),\
																				Point2i(screenWidth, screenHeight), \
																				Point2i(screenWidth, screenHeight), \
																				90);

std::shared_ptr<Texture> mirror = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.99), false, kReflect));

std::shared_ptr<Texture> wall1 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.75)));
std::shared_ptr<Texture> wall2 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0)));
std::shared_ptr<Texture> wall3 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.75, 0.25, 0.25)));
std::shared_ptr<Texture> wall4 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.25, 0.75, 0.25)));

std::shared_ptr<Texture> tex1 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.25, 0.25, 0.7)));
std::shared_ptr<Texture> tex2 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.3)));
std::shared_ptr<Texture> tex3 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.8)));
std::shared_ptr<Texture> tex4 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.15)));
std::shared_ptr<Texture> tex5 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.9, 0.2, 0.2)));
std::shared_ptr<Texture> tex6 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.2)));

std::vector<Object *> objects = {

	new Cylinder(Point3d(-10, -60, -145), Point3d(-10, -52, -145), 35, mirror), // Mirror

	new Sphere(Point3d(-15,  -25, -160.0),	15,	tex3),	// Body

	new Sphere(Point3d(-24,  -33, -151.0),	6,	tex2),	// Left down foot
	new Sphere(Point3d(-4,  -35, -160.0),	6,		tex2),	// right down foot

	new Sphere(Point3d(-23.5,  -17, -148.0),	6,tex2),	// Left up foot
	new Sphere(Point3d(-2,  -20, -158.0),	6,		tex2),	// Right up foot

	new Sphere(Point3d(-9,  -2, -160.0),	18,		tex3),	// Head

	new Sphere(Point3d(-15,  10.3, -147.0),	6,	tex4),	// Ear
	new Sphere(Point3d(4,  9, -156.0),	6,			tex4),

	new Sphere(Point3d(-6.5,  0.3, -143.6),	3,	tex4),	// Eye
	new Sphere(Point3d(2.5,  0, -147.5),	3,		tex4),

	new Cylinder(Point3d(-3, -7, -150), Point3d(4, -10, -132), 1.8, tex5),	// Nose

	new Sphere(Point3d(-0.8,  -13.3, -149.8),	2,tex7),	// Mouth

	new Sphere(Point3d(0, -1e5-60, -160),		1e5, 	wall1),
	new Sphere(Point3d(0, 1e5+60, -160), 		1e5, 	wall1),
	new Sphere(Point3d(0, 0, -1e5-225), 		1e5, 	wall1),
	new Sphere(Point3d(-1e5-70, 0, -175), 	1e5, 	wall3),
	new Sphere(Point3d(1e5+70, 0, -175),  	1e5, 	wall4),
	new Sphere(Point3d(0, 959.8, -160.0), 	900, 	light)
};

std::vector<Light *> lights = {
	new DirectionalLight(Vector3d(-0.3, 0.3, -1), Vector3d(0.8))
};
