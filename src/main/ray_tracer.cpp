/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-30 08:52:52
**/

#include "../core/scene.hpp"
#include "../core/window.hpp"
#include "../object/mesh.hpp"

void test(Scene &scene, int samples, bool accelerate)
{

	// if (accelerate) scene.accelerate();

	Window win(scene.name(), scene.width(), scene.height());
	win.render(scene, samples);
}

int main(int argc, char **argv)
{
	// test(Scene::DepthOfField, argc >= 2 ? atoi(argv[1]) : 4, argc == 3);
	// test(Scene::CornellBox, argc == 2 ? atoi(argv[1]) : 4, argc == 3);
	// return 0;

	//Camera *cam = new PerspectiveCamera(Point3d(0, 0, 3), Vector3d(0, 0, -1.0), Point2i(512, 512),
	//																		Point2i(512, 512), 90);
	Mesh *mesh = new Mesh("cube");
	mesh->subdivide();
	// Scene s("mesh", 512, 512, cam, obj);
	// test(s, 4, 0);

	return 0;
}
