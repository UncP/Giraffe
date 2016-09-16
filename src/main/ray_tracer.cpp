/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-06-30 08:52:52
**/

#include <memory>

#include "../core/scene.hpp"
#include "../core/window.hpp"

int main(int argc, char **argv)
{
	int screenWidth = 512, screenHeight = 512;

	using namespace Giraffe;

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

	std::shared_ptr<Texture> sphere1 = std::shared_ptr<Texture>(
		new ConstantTexture(Color(0.25, 0.25, 0.75)));
		// new ImageTexture("../texture/earth.png", 1, true));
		// new BrickTexture(Color(1, 1, 0), Color(0, 1, 1), 0.2, 0.08, 0.016, true));
		// new MarbleTexture(Color(1), Color(2, 2, 0.5), Color(0.5), 0.1, true));
		// new MarbleTexture(Color(0.8), Color(0.8, 0.8, 0.2), Color(0.05), 0.1));
		// new StripeTexture(Color(), Color(1), Yaxis, 5));
		// new NoiseTexture(Color(0.8, 0.8, 0.2), Color(0.05), 0.1, true));
		// new ConstantTexture(Color(0.999), Color(), kReflect));
	std::shared_ptr<Texture> sphere2 = std::shared_ptr<Texture>(
		new BrickTexture(Color(0.5, 0.1, 0.1), Color(0.5), 0.2, 0.08, 0.016, true));
		// new MarbleTexture(Color(1), Color(0.5, 2, 2), Color(0.5), 0.1, true));
		// new StripeTexture(Color(), Color(1), Xaxis, 4));
		// new MarbleTexture(Color(0.8), Color(0.2, 0.8, 0.8), Color(0.05), 0.1));
		// new NoiseTexture(Color(0.2, 0.8, 0.8), Color(0.05), 0.1));
		// new ConstantTexture(Color(0.999), Color(), kReflect));
	std::shared_ptr<Texture> sphere3 = std::shared_ptr<Texture>(
		new MarbleTexture(Color(1), Color(0.6, 0.5, 2), Color(0.5), 0.1, true));
	std::shared_ptr<Texture> sphere4 = std::shared_ptr<Texture>(
		new MarbleTexture(Color(1), Color(0.2, 1.7, 0.5), Color(0.5), 0.1, true));
	std::shared_ptr<Texture> sphere5 = std::shared_ptr<Texture>(
		new StripeTexture(Color(0.4, 0.2, 0.1), Color(2), Yaxis, 3, true));
	std::shared_ptr<Texture> sphere6 = std::shared_ptr<Texture>(
		new MarbleTexture(Color(1), Color(4, 1, 2), Color(0.5), 0.1, true));
	std::shared_ptr<Texture> light = std::shared_ptr<Texture>(
		new ConstantTexture(Color(16), true));
		// new StripeTexture(Color(), Color(1), Xaxis, 0.1, Color(16)));

	std::vector<Object *> obj = {
		new Sphere(Point3d(0, -1e5-60, -160),		1e5, 	wall1),
		new Sphere(Point3d(0, 1e5+60, -160), 		1e5, 	wall1),
		new Sphere(Point3d(0, 0, -1e5-225), 		1e5, 	wall5),
		new Sphere(Point3d(0, 0, 1e5+125), 			1e5, 	wall2),
		new Sphere(Point3d(-1e5-70, 0, -175), 	1e5, 	wall3),
		new Sphere(Point3d(1e5+70, 0, -175),  	1e5, 	wall4),
		// new Sphere(Point3d(-33, -40, -185.0),		20,		sphere1),
		// new Sphere(Point3d(37, -44, -145.0),		16,		sphere2),
		// new Sphere(Point3d(0,  -30, -175.0),		30,		sphere1),
		// new Sphere(Point3d(-1,  -50, -185.0),		10,		sphere3),
		// new Sphere(Point3d(-23,  -48, -185.0),	12,		sphere5),
		// new Sphere(Point3d(-50,  -45, -185.0),	15,		sphere6),
		// new Sphere(Point3d(-45,  -52, -130.0),	8,		sphere2),
		// new Sphere(Point3d(45,  -35, -200.0),		25,		sphere1),
		// new Sphere(Point3d(50,  -48, -135.0),		10,		sphere4)
		new Sphere(Point3d(0, 959.8, -160.0), 	900, 	light)
	};
	Scene CornellBox("cornell box", cam, obj);

	Window win(CornellBox.name(), screenWidth, screenHeight);
	win.render(CornellBox, argc == 2 ? atoi(argv[1]) : 4);
	return 0;
}
