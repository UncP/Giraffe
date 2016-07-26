/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-30 08:52:52
**/

#include "window.hpp"

int main(int argc, char **argv)
{
	Window win(1024, 768, "rayTracer");
	std::vector<Sphere *> spheres;
	spheres.push_back(new Sphere(Vec3(0.0, 1e5-40, -50.0), 1e5, Vec3(0.75)));
	spheres.push_back(new Sphere(Vec3(0.0, 1e5+40, -50.0), 1e5, Vec3(0.75)));
	spheres.push_back(new Sphere(Vec3(0.0, 0.0, -1e5-100), 1e5, Vec3(0.75)));
	spheres.push_back(new Sphere(Vec3(0.0, 0.0, 1e5+180), 1e5, Vec3(0.0)));
	spheres.push_back(new Sphere(Vec3(-1e5-50, 0.0, -50.0), 1e5, Vec3(0.75, 0.25, 0.25)));
	spheres.push_back(new Sphere(Vec3(1e5+50, 0.0, -50.0), 1e5, Vec3(0.25, 0.25, 0.75)));
	spheres.push_back(new Sphere(Vec3(-20.0, -24.5, -55.0), 15.5, Vec3(0.999), Vec3(), kReflect));
	spheres.push_back(new Sphere(Vec3(25.0, -26.5, -15.0), 13.5, Vec3(0.999), Vec3(), kRefract));

	spheres.push_back(new Sphere(Vec3(0.0, 839.7, -25.0), 800, Vec3(1.0), Vec3(8, 8, 8)));

	Camera cam(Vec3(0.0, 0.0, 200.0), Vec3(0.0, 0.0, -1.0));
	win.rayTrace(cam, spheres, 8);
	win.show();
	win.save("demo.ppm");
	getchar();

	return 0;
}
