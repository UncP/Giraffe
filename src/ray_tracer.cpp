/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-30 08:52:52
**/

#include "scene.hpp"
#include "window.hpp"
#include "ray.hpp"

void test(const Scene &scene, int samples)
{
	Window win(	scene.width(), scene.height(), scene.name().c_str());
	win.render(scene, samples);
	win.show();

	win.save_ppm("demo.ppm");
	win.save_png("demo.png");

	getchar();
}

int main(int argc, char **argv)
{
	// ProjectiveCamera cam(Vec(0.0, 0.0, 100.0), Vec(0.0, 0.0, -1.0));
	// Vec a1(0, 0, 0), a2(512, 512, 0);
	// Vec b1 = cam.rasterToScreen() * a1;
	// Vec b2 = cam.rasterToScreen() * a2;
	// std::cout << b1 << b2;
	// return 0;
	// test(Scene::DepthOfField, argc == 2 ? atoi(argv[1]) : 4);
	// test(Scene::CornellBox, argc == 2 ? atoi(argv[1]) : 4);


	return 0;
}
