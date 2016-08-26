/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-27 21:01:11
**/

#include "scene.hpp"

/*
static Camera *cam2 = new ThinLenCamera(Vec(0, 0, 0), \
																				Vec(0, 0, -1), \
																				Vec(0, 1.0, 0), \
																				6, 250, \
																				screenWidth, screenHeight);

static std::vector<Object *> obj2 = {
	new Sphere(Vec(-140, 0, -425), 	25, 	Vec(1.0, 0, 0)),
	new Sphere(Vec(-120, 0, -400), 	25, 	Vec(1.0, 0, 0)),
	new Sphere(Vec(-100, 0, -375), 	25, 	Vec(1.0, 0, 0)),
	new Sphere(Vec(-80, 0, -350), 	25, 	Vec(1.0, 0, 0)),
	new Sphere(Vec(-60, 0, -325), 	25, 	Vec(1.0, 0, 0)),
	new Sphere(Vec(-40, 0, -300), 	25, 	Vec(1.0, 0, 0)),
	new Sphere(Vec(-20, 0, -275), 	25, 	Vec(1.0, 0, 0)),
	new Sphere(Vec(	0, 0,  -250),		25, 	Vec(1.0, 0, 0)),
	new Sphere(Vec(	20, 0, -225),		25, 	Vec(1.0, 0, 0)),
	new Sphere(Vec(	40, 0, -200), 	25, 	Vec(1.0, 0, 0)),
	new Sphere(Vec(	60, 0, -175), 	25, 	Vec(1.0, 0, 0)),
	new Sphere(Vec(0, -1e5-25, 0), 	1e5, 	Vec(0.75)),
	new Sphere(Vec(0, 136, -250), 	33, 	Vec(1.0), Vec(20, 20, 20))
};

Scene Scene::DepthOfField(Scene("depth of field", screenWidth, screenHeight, cam2, obj2));
*/

void Scene::accelerate() {
	BVH *bvh = new BVH();
	if (!bvh) {
		std::cerr << "acceleration failed :(\n";
		return ;
	}
	bvh->build(objects_);
	objects_.clear();
	// std::cout << bvh;
	objects_.push_back(static_cast<Object *>(bvh));
	accelerate_ = true;
}

Scene::~Scene()
{
	delete camera_;
	if (!accelerate_)
		std::for_each(objects_.begin(), objects_.end(), [](Object *obj) { delete obj; });
}
