/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *				Puppy
 *    > Created Time: 2016-10-21 22:56:18
**/

int screenWidth = 512, screenHeight = 512;

Camera *camera = new PerspectiveCamera(	Point3d(0, 0, 0), 	\
																				Vector3d(0, 0, -1.0),\
																				Point2i(screenWidth, screenHeight), \
																				Point2i(screenWidth, screenHeight), \
																				90);

std::shared_ptr<Texture> wall1 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.75)));
std::shared_ptr<Texture> wall2 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0)));
std::shared_ptr<Texture> wall3 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.2, 0.2, 0.85)));
std::shared_ptr<Texture> wall4 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.75, 0.2, 0.2)));

std::shared_ptr<Texture> tex1 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.5), false));
std::shared_ptr<Texture> tex2 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.999), false));
std::shared_ptr<Texture> tex3 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.3)));
std::shared_ptr<Texture> tex4 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.15)));
std::shared_ptr<Texture> tex5 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.2, 0.8, 0.2)));
std::shared_ptr<Texture> tex6 = std::shared_ptr<Texture>(
	new StripeTexture(Color(0.8, 0.8, 0.1), Color(0.7), Xaxis, 0.5));

std::vector<Object *> objects = {

	new Sphere(Point3d(0,   -35, -160.0), 20,  tex2),  // Body
	new Sphere(Point3d(0,   -41, -140),   2.5, tex5),  // Mouth
	new Sphere(Point3d(0,   -31, -143.0), 6,   tex3),  // Nose
	new Sphere(Point3d(-9,  -23, -144.5), 3,   tex4),  // Eye
	new Sphere(Point3d(9,   -23, -144.5), 3,   tex4),
	new Sphere(Point3d(0,   -22, -160),   10,  tex6),  // Hat
	new Sphere(Point3d(-9.5,-52, -152.0), 8,   tex2),  // Foot
	new Sphere(Point3d(-13, -52, -170.0), 8.5, tex2),
	new Sphere(Point3d(9.5, -52, -152.0),	8,   tex2),
	new Sphere(Point3d(13,  -52, -170.0),	8.5, tex2),

	new Sphere(Point3d(0, -1e5-60, -160),     1e5,  wall1),
	new Sphere(Point3d(0,  1e5+60, -160),     1e5,  wall1),
	new Sphere(Point3d(0,       0, -1e5-225), 1e5,  wall1),
	new Sphere(Point3d(0,       0,  1e5+125), 1e5,  wall2),
	new Sphere(Point3d(-1e5-70, 0, -175),     1e5,  wall3),
	new Sphere(Point3d(1e5+70,  0, -175),     1e5,  wall4),
};

std::vector<Light *> lights = {
	new PointLight(Point3d(0, 40, -160.0), Vector3d(2056)),
};
