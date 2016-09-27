/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-06-30 08:52:52
**/

#include <memory>

#include "../math/matrix.hpp"
#include "../core/scene.hpp"
#include "../core/window.hpp"
#include "../object/sphere.hpp"
#include "../object/triangle.hpp"
#include "../object/cube.hpp"
#include "../object/cylinder.hpp"
#include "../texture/constant.hpp"
#include "../texture/stripe.hpp"
#include "../texture/noise.hpp"
#include "../texture/marble.hpp"
#include "../texture/brick.hpp"
#include "../texture/image.hpp"
#include "../texture/bump_brick.hpp"

int main(int argc, char **argv)
{
	using namespace Giraffe;

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
		// new MarbleTexture(Color(0.8), Color(0.75, 0.25, 0.25), Color(0.05), 0.1));
		// new ConstantTexture(Color(0.999), Color(), kReflect));
	std::shared_ptr<Texture> wall4 = std::shared_ptr<Texture>(
		new ConstantTexture(Color(0.25, 0.75, 0.25)));
		// new MarbleTexture(Color(0.8), Color(0.25, 0.75, 0.25), Color(0.05), 0.1));
		// new ConstantTexture(Color(0.25, 0.75, 0.25)));
		// new ConstantTexture(Color(0.999), Color(), kReflect));
	std::shared_ptr<Texture> wall5 = std::shared_ptr<Texture>( // 4.8e-5  7.2e-6
		new BumpBrickTexture(Color(0.5, 0.1, 0.1), Color(0.5), 1.2e-4, 1.2e-4, 1.44e-5));
		// new StripeTexture(Color(), Color(1), Xaxis, 3));
	std::shared_ptr<Texture> wall6 = std::shared_ptr<Texture>(
		// new MarbleTexture(Color(0.8), Color(0.25, 0.25, 0.75), Color(0.05), 0.1));
		new NoiseTexture(Color(0.8, 0.8, 0.2), Color(0.05), 0.1, false));
		// new BrickTexture(Color(0.1, 0.1, 0.5), Color(0.5), 25, 10, 2));

		// new BrickTexture(Color(0.5, 0.1, 0.1), Color(0.5), 0.2, 0.08, 0.016, true));
		// new MarbleTexture(Color(1), Color(0.5, 2, 2), Color(0.5), 0.1, true));
		// new StripeTexture(Color(), Color(1), Xaxis, 4));
		// new MarbleTexture(Color(0.8), Color(0.2, 0.8, 0.8), Color(0.05), 0.1));
		// new NoiseTexture(Color(0.2, 0.8, 0.8), Color(0.05), 0.1));
		// new ConstantTexture(Color(0.999), Color(), kReflect));

		// new StripeTexture(Color(), Color(1), Yaxis, 5));
		// new BrickTexture(Color(1, 1, 0), Color(0, 1, 1), 0.2, 0.08, 0.016, true));
		// new MarbleTexture(Color(1), Color(2, 2, 0.5), Color(0.5), 0.1, true));
		// new MarbleTexture(Color(0.8), Color(0.8, 0.8, 0.2), Color(0.05), 0.1));
		// new NoiseTexture(Color(0.8, 0.8, 0.2), Color(0.05), 0.1, true));
		// new ImageTexture("../texture/earth.png"));
	std::shared_ptr<Texture> tex1 = std::shared_ptr<Texture>(
		new ConstantTexture(Color(0.25, 0.25, 0.75)));
	std::shared_ptr<Texture> tex2 = std::shared_ptr<Texture>(
		new ConstantTexture(Color(0.999), false, kReflect));
	std::shared_ptr<Texture> tex3 = std::shared_ptr<Texture>(
		new MarbleTexture(Color(1), Color(0.6, 0.5, 2), Color(0.5), 0.1));
	std::shared_ptr<Texture> tex4 = std::shared_ptr<Texture>(
		new MarbleTexture(Color(1), Color(0.2, 1.7, 0.5), Color(0.5), 0.1, true));
	std::shared_ptr<Texture> tex5 = std::shared_ptr<Texture>(
		new StripeTexture(Color(0.4, 0.2, 0.1), Color(2), Yaxis, 3, true));
	std::shared_ptr<Texture> tex6 = std::shared_ptr<Texture>(
		new MarbleTexture(Color(1), Color(4, 1, 2), Color(0.5), 0.1, true));
	std::shared_ptr<Texture> light = std::shared_ptr<Texture>(
		new ConstantTexture(Color(16), true));
		// new StripeTexture(Color(), Color(1), Xaxis, 0.1, Color(16)));

	// Matrix a = rotateX(45);
	// Matrix b = rotateY(45);
	// Vector3d o(a(Vector3d(0, 1, 0)));
	// std::cout << o;
	// return 0;

	std::vector<Object *> obj = {
		// new Cube(Point3d(20, -45, -170), 20, 20, 30, tex1, b),
		new Cylinder(Point3d(-20, -45, -150), Point3d(20, -25, -175), 15, tex1),
		// new Triangle(Point3d(0, -30, -150), Point3d(40, 0, -160), Point3d(0, 0, -150), tex3),
		// new Sphere(Point3d(-33, -40, -185.0),		20,		tex1),
		// new Sphere(Point3d(37, -44, -145.0),		16,		tex2),
		// new Sphere(Point3d(0,  -30, -175.0),		30,		tex1),
		// new Sphere(Point3d(-1,  -50, -185.0),		10,		tex3),
		// new Sphere(Point3d(-23,  -48, -185.0),	12,		tex5),
		// new Sphere(Point3d(-50,  -45, -185.0),	15,		tex6),
		// new Sphere(Point3d(-45,  -52, -130.0),	8,		tex2),
		// new Sphere(Point3d(45,  -35, -200.0),		25,		tex1),
		// new Sphere(Point3d(50,  -48, -135.0),		10,		tex4)
		new Sphere(Point3d(0, -1e5-60, -160),		1e5, 	wall1),
		new Sphere(Point3d(0, 1e5+60, -160), 		1e5, 	wall1),
		new Sphere(Point3d(0, 0, -1e5-225), 		1e5, 	wall1),
		new Sphere(Point3d(0, 0, 1e5+125), 			1e5, 	wall2),
		new Sphere(Point3d(-1e5-70, 0, -175), 	1e5, 	wall3),
		new Sphere(Point3d(1e5+70, 0, -175),  	1e5, 	wall4),
		new Sphere(Point3d(0, 959.8, -160.0), 	900, 	light)
	};
	Scene CornellBox("cornell box", cam, obj);

	Window win(CornellBox.name(), screenWidth, screenHeight);
	win.render(CornellBox, argc == 2 ? atoi(argv[1]) : 4);
	return 0;
}
