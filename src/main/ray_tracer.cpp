/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-30 08:52:52
**/

#include <memory>

#include "../core/scene.hpp"
#include "../core/window.hpp"
#include "../object/mesh.hpp"

void test(int samples)
{
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
	std::shared_ptr<Texture> sphere1 = std::shared_ptr<Texture>(
		new MarbleTexture(Color(0.8), Color(0.3, 0.15, 0.075), Color(0.2), 0.1));
		// new WoodTexture(Color(0.6, 0.3, 0.15)));
		// new NoiseTexture(Color(1, 1, 0), Color(0, 1, 1), 0.1));
		// new StripeTexture(Color(), Color(1), Yaxis, 6));
	std::shared_ptr<Texture> sphere2 = std::shared_ptr<Texture>(
		new NoiseTexture(Color(1, 0, 1), Color(0.5, 0.5, 0.5), 0.1));
		// new StripeTexture(Color(), Color(1), Xaxis, 3));
	std::shared_ptr<Texture> light = std::shared_ptr<Texture>(
		new ConstantTexture(Color(0.999), Color(16, 16, 16)));

	std::vector<Object *> obj = {
		new Sphere(Point3d(0, 1e5-60, -160),		1e5, 	wall1),
		new Sphere(Point3d(0, 1e5+60, -160), 		1e5, 	wall1),
		new Sphere(Point3d(0, 0, -1e5-225), 		1e5, 	wall1),
		new Sphere(Point3d(0, 0, 1e5+125), 			1e5, 	wall2),
		new Sphere(Point3d(-1e5-70, 0, -175), 	1e5, 	wall3),
		new Sphere(Point3d(1e5+70, 0, -175),  	1e5, 	wall4),
		new Sphere(Point3d(-33, -40, -185.0),		20,		sphere1),
		// new Sphere(Point3d(37, -44, -145.0),		16,		sphere2),
		new Sphere(Point3d(0, 959.8, -160.0), 	900, 	light)
	};

	Scene CornellBox("cornell box", cam, obj);

	Window win(CornellBox.name(), screenWidth, screenHeight);
	win.render(CornellBox, samples);
}

int main(int argc, char **argv)
{
	test(argc == 2 ? atoi(argv[1]) : 4);
	return 0;
}
