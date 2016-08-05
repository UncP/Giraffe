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
#include "mesh.hpp"

void test(Scene &scene, int samples, bool accelerate)
{

#ifdef AC
	if (accelerate) scene.accelerate();
#endif

	Window win(scene.width(), scene.height(), scene.name().c_str());
	win.render(scene, samples);
}

int main(int argc, char **argv)
{
	// test(Scene::MotionBlur, argc >= 2 ? atoi(argv[1]) : 4, 0);
	// test(Scene::DepthOfField, argc >= 2 ? atoi(argv[1]) : 4, argc == 3);
	// test(Scene::CornellBox, argc == 2 ? atoi(argv[1]) : 4);
	Mesh mesh("cube");
	mesh.print();
	return 0;
}
