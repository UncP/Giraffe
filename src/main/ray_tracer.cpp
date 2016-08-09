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
	// test(Scene::MotionBlur, argc >= 2 ? atoi(argv[1]) : 4, 0);
	// test(Scene::DepthOfField, argc >= 2 ? atoi(argv[1]) : 4, argc == 3);
	test(Scene::CornellBox, argc == 2 ? atoi(argv[1]) : 4, argc == 3);
	return 0;
	std::vector<Object *> obj = {
		new Mesh("cube"),
		// new Sphere(       Vec(0, 30, 0),  10,  Vec(1.0), Vec(4, 4, 4))
	};
/*
	Camera *cam = new OrthographicCamera(Vec(10, 0, 10), Vec(-0.5, 0, -1), Vec(0, 1, 0),
		5, 5, 512, 512);
	Scene s("mesh", 512, 512, cam, obj);
	// s.accelerate();
	test(s, 4, 0);
*/
	return 0;
}
