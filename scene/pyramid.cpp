/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *				Pyramid
 *    > Created Time: 2016-09-27 20:51:17
**/

int screenWidth = 512, screenHeight = 512;
Camera *cam = new PerspectiveCamera(Point3d(0, 0, 0), 	\
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
	new ConstantTexture(Color(0.9, 0.15, 0.04)));
std::shared_ptr<Texture> tex2 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.15, 0.04, 0.9)));
std::shared_ptr<Texture> tex3 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.04, 0.9, 0.15)));
std::shared_ptr<Texture> tex4 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.8, 0.8, 0.2)));

std::vector<Object *> obj = {
	new Cylinder(Point3d(-45, -60, -160), Point3d(-45, -40, -160), 12, tex1),
	new Cylinder(Point3d(-15, -60, -160), Point3d(-15, -40, -160), 12, tex1),
	new Cylinder(Point3d(15, -60, -160), Point3d(15, -40, -160), 12, tex1),
	new Cylinder(Point3d(45, -60, -160), Point3d(45, -40, -160), 12, tex1),

	new Cylinder(Point3d(-30, -40, -160), Point3d(-30, -20, -160), 12, tex2),
	new Cylinder(Point3d(0, -40, -160), Point3d(0, -20, -160), 12, tex2),
	new Cylinder(Point3d(30, -40, -160), Point3d(30, -20, -160), 12, tex2),

	new Cylinder(Point3d(-15, -20, -160), Point3d(-15, 0, -160), 12, tex3),
	new Cylinder(Point3d(15, -20, -160), Point3d(15, 0, -160), 12, tex3),

	new Cylinder(Point3d(0, 0, -160), Point3d(0, 20, -160), 12, tex4),

	new Sphere(Point3d(0, -1e5-60, -160),		1e5, 	wall1),
	new Sphere(Point3d(0, 1e5+60, -160), 		1e5, 	wall1),
	new Sphere(Point3d(0, 0, -1e5-225), 		1e5, 	wall1),
	new Sphere(Point3d(0, 0, 1e5+125), 			1e5, 	wall2),
	new Sphere(Point3d(-1e5-70, 0, -175), 	1e5, 	wall3),
	new Sphere(Point3d(1e5+70, 0, -175),  	1e5, 	wall4),
	new Sphere(Point3d(0, 959.8, -160.0), 	900, 	light)
};
