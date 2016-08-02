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

void test(const Scene &scene, int samples)
{
	Window win(scene.width(), scene.height(), scene.name().c_str());
	win.render(scene, samples);
	win.show();

	// win.save_ppm("demo.ppm");
	win.save_png("demo.png");

	getchar();
}

int main(int argc, char **argv)
{
	// test(Scene::DepthOfField, argc == 2 ? atoi(argv[1]) : 4);
	test(Scene::CornellBox, argc == 2 ? atoi(argv[1]) : 4);


	return 0;
}
