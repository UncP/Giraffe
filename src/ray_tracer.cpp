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
	Window win(512, 512, "rayTracer");
	std::vector<Sphere *> spheres;
	spheres.push_back(new Sphere(Vec3(0.0, 1e5+50, -50.0), 1e5, Vec3(0.75, 0.75, 0.75)));
	spheres.push_back(new Sphere(Vec3(0.0, -1e5-50, -50.0), 1e5, Vec3(0.75, 0.75, 0.75)));

	spheres.push_back(new Sphere(Vec3(0.0, 0.0, -1e5-100), 1e5, Vec3(0.75, 0.75, 0.75)));
	spheres.push_back(new Sphere(Vec3(0.0, 0.0, 1e5+150), 1e5, Vec3(0.0)));

	spheres.push_back(new Sphere(Vec3(-1e5-50, 0.0, -50.0), 1e5, Vec3(0.25, 0.25, 0.75)));
	spheres.push_back(new Sphere(Vec3(1e5+50, 0.0, -50.0), 1e5, Vec3(0.75, 0.25, 0.25)));
	spheres.push_back(new Sphere(Vec3(-20.0, -32.5, -55.0), 17.5, Vec3(0.999), kReflect));
	spheres.push_back(new Sphere(Vec3(30.0, -40.0, -20.0), 12.5, Vec3(0.5), kRefract));
	std::vector<Light *> light;
	light.push_back(new PointLight(Vec3(0.0, 35.0, -36), 12));

	Vec3 eye(0.0, 0.0, 100.0);
	win.rayTrace(eye, 60.0, light, spheres);
	win.show();
	win.save("demo.ppm");
	getchar();

	return 0;
}
