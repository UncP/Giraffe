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

int main(int argc, char **argv)
{
	Window win(512, 512, Scene::CornellBox.name().c_str());
	win.render(Scene::CornellBox, argc == 2 ? atoi(argv[1]) : 4);
	win.show();
	win.save_ppm("demo.ppm");
	win.save_png("demo.png");

	getchar();

	return 0;
}
