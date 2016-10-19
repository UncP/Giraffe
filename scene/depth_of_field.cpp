/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *				Depth of field
 *    > Created Time: 2016-09-15 10:45:04
**/

int screenWidth = 512, screenHeight = 512;

Camera *cam = new PerspectiveCamera(Point3d(0, 0, 0), 	\
																		Vector3d(0, 0, -1.0),\
																		Point2i(screenWidth, screenHeight), \
																		Point2i(screenWidth, screenHeight), \
																		90, 12, 150);

std::shared_ptr<Texture> wall1 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.75)));
std::shared_ptr<Texture> wall2 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0)));
std::shared_ptr<Texture> wall3 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.75, 0.25, 0.25)));
std::shared_ptr<Texture> wall4 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.25, 0.75, 0.25)));


std::shared_ptr<Texture> tex1 = std::shared_ptr<Texture>(
	new ConstantTexture(Color(0.25, 0.25, 0.75)));
std::shared_ptr<Texture> light = std::shared_ptr<Texture>(
	new ConstantTexture(Color(16), true));

std::vector<Object *> obj = {

	new Sphere(Point3d(-55, -45, -210), 15, tex1),
	new Sphere(Point3d(-40, -45, -195), 15, tex1),
	new Sphere(Point3d(-25, -45, -180), 15, tex1),
	new Sphere(Point3d(-10, -45, -165), 15, tex1),
	new Sphere(Point3d(5, -45, -150), 15, tex1),
	new Sphere(Point3d(20, -45, -135), 15, tex1),
	new Sphere(Point3d(35, -45, -120), 15, tex1),
	new Sphere(Point3d(50, -45, -105), 15, tex1)

	new Sphere(Point3d(0, -1e5-60, -160),		1e5, 	wall1),
	new Sphere(Point3d(0, 1e5+60, -160), 		1e5, 	wall1),
	new Sphere(Point3d(0, 0, -1e5-225), 		1e5, 	wall1),
	new Sphere(Point3d(0, 0, 1e5+125), 			1e5, 	wall2),
	new Sphere(Point3d(-1e5-70, 0, -175), 	1e5, 	wall3),
	new Sphere(Point3d(1e5+70, 0, -175),  	1e5, 	wall4),

	new Sphere(Point3d(0, 959.8, -160.0), 	900, 	light),
};
