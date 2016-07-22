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
	spheres.push_back(new Sphere(Vec3(0.0, 0.0, -1050.0), 1000.0, Color(0.7, 0.5, 0.6)));
	// floor
	spheres.push_back(new Sphere(Vec3(0.0, -1005.0, -20.0), 1000.0, Color(0.6, 0.6, 0.6)));

	// scene
	spheres.push_back(new Sphere(Vec3(2.0, 0.0, -20.0), 5.0, Color::Red));
	spheres.push_back(new Sphere(Vec3(-4.0, -1.0, -8.0), 1.0, Color::Blue));
	spheres.push_back(new Sphere(Vec3(7.0, 6.0, -15.0), 1.5, Color::Yellow));
	spheres.push_back(new Sphere(Vec3(2.0, -1.5, -5.0), 0.5, Color(0.2, 0.8, 0.3)));
	spheres.push_back(new Sphere(Vec3(-8.0, 5.0, -18.0), 2.0, Color::White));

	std::vector<Light *> light;
	Light *l1 = new PointLight(Vec3(10, 30, 10));
	light.push_back(l1);

	Vec3 eye(0);
	win.rayTrace(eye, spheres, light);
	win.show();
	getchar();

	return 0;
}
