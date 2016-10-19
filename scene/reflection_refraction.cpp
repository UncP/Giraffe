/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *				Reflection & Refraction
 *    > Created Time: 2016-10-19 15:26:59
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
	new ConstantTexture(Color(0.75, 0.25, 0.25)));
std::shared_ptr<Texture> wall4 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.25, 0.75, 0.25)));

std::shared_ptr<Texture> tex1 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.999), false, kReflect));

std::shared_ptr<Texture> tex2 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.999), false, kRefract));

std::vector<Object *> objects = {
		new Sphere(Point3d(-35,  -42, -180.0),	18,		tex1),
		new Sphere(Point3d(38,  -45, -150.0),		15,		tex2),

		new Sphere(Point3d(0, -1e5-60, -160),		1e5, 	wall1),
		new Sphere(Point3d(0, 1e5+60, -160), 		1e5, 	wall1),
		new Sphere(Point3d(0, 0, -1e5-225), 		1e5, 	tex1),
		new Sphere(Point3d(0, 0, 1e5+125), 			1e5, 	wall2),
		new Sphere(Point3d(-1e5-70, 0, -175), 	1e5, 	wall3),
		new Sphere(Point3d(1e5+70, 0, -175),  	1e5, 	wall4),
		new Sphere(Point3d(0, 959.8, -160.0), 	900, 	light)
};
