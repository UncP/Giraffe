/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-27 21:01:11
**/

#include "scene.hpp"

static Camera cam(Vec3(0.0, 0.0, 200.0), Vec3(0.0, 0.0, -1.0));
static std::vector<Sphere *> spheres = {
	new Sphere(Vec3(0.0, 1e5-40, -50.0), 1e5, Vec3(0.75)),
	new Sphere(Vec3(0.0, 1e5+40, -50.0), 1e5, Vec3(0.75)),
	new Sphere(Vec3(0.0, 0.0, -1e5-100), 1e5, Vec3(0.75)),
	new Sphere(Vec3(0.0, 0.0, 1e5+180), 1e5, Vec3(0.0)),
	new Sphere(Vec3(-1e5-50, 0.0, -50.0), 1e5, Vec3(0.75, 0.25, 0.25)),
	new Sphere(Vec3(1e5+50, 0.0, -50.0), 1e5, Vec3(0.25, 0.75, 0.25)),
	new Sphere(Vec3(-20.0, -24.5, -55.0), 15.5, Vec3(0.999), Vec3(), kReflect),
	new Sphere(Vec3(25.0, -26.5, -15.0), 13.5, Vec3(0.999), Vec3(), kRefract),
	new Sphere(Vec3(0.0, 839.7, -25.0), 800, Vec3(1.0), Vec3(8, 8, 8))
};

Scene Scene::CornellBox(Scene("cornell box", cam, spheres));