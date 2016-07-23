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
	Window win(500, 500, "rayTracer");
	std::vector<Sphere *> spheres;

	// background
	spheres.push_back(new Sphere(Vec3(0.0, 0.0, -1050.0), 1000.0, Vec3(0.7, 0.5, 0.6)));
	// floor
	spheres.push_back(new Sphere(Vec3(0.0, -1005.0, -20.0), 1000.0, Vec3(0.6, 0.6, 0.6)));

	// scene
	spheres.push_back(new Sphere(Vec3(2.0, 0.0, -20.0), 5.0, Vec3(1.0, 0.0, 0.0)));
	spheres.push_back(new Sphere(Vec3(-4.0, -1.0, -8.0), 1.0, Vec3(0.0, 0.0, 1.0)));
	spheres.push_back(new Sphere(Vec3(7.0, 6.0, -15.0), 1.5, Vec3(1.0, 1.0, 0.0), kPhong));
	spheres.push_back(new Sphere(Vec3(2.0, -1.5, -5.0), 0.5, Vec3(0.2, 0.8, 0.3), kRefract));
	spheres.push_back(new Sphere(Vec3(-8.0, 5.0, -18.0), 2.0, Vec3(1.0), kReflect));

	std::vector<Light *> light;
	light.push_back(new PointLight(Vec3(5, 25, 0)));
	// light.push_back(new DirectionalLight(Vec3(-10, -10, -10)));

	Vec3 eye(0);
	win.rayTrace(eye, 75.0, light, spheres);
	win.show();
	getchar();

	return 0;
}
