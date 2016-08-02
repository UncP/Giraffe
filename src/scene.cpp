/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-27 21:01:11
**/

#include "scene.hpp"

static const int sceneWidth = 512, sceneHeight = 512;
// static const int sceneWidth = 1024, sceneHeight = 768;
static Camera *cam = new PerspectiveCamera(	Vec(0, 0, 0), 	\
																						Vec(0, -0.07, -1.0),\
																						Vec(0, 1.0, 0),		\
																						sceneWidth, sceneHeight);
static std::vector<Object *> spheres = {
	new Sphere(Vec(0, 1e5-40, -250),		1e5, 	Vec(0.75)),
	new Sphere(Vec(0, 1e5+40, -250), 		1e5, 	Vec(0.75)),
	new Sphere(Vec(0, 0, -1e5-300), 		1e5, 	Vec(0.75)),
	new Sphere(Vec(0, 0, 1e5+50), 			1e5, 	Vec(0)),
	new Sphere(Vec(-1e5-50, 0, -250), 	1e5, 	Vec(0.75, 0.25, 0.25)),
	new Sphere(Vec(1e5+50, 0, -250),  	1e5, 	Vec(0.25, 0.75, 0.25)),
	new Sphere(Vec(25.0, -24.5, -255.0),15.5,	Vec(0.999), 		Vec(), 		kReflect),
	new Sphere(Vec(-20, -26.5, -215.0),	13.5,	Vec(0.999), 		Vec(), 		kRefract),
	new Sphere(Vec(0, 839.8, -225.0), 	800, 	Vec(1.0), 			Vec(8, 8, 8))
};

Scene Scene::CornellBox(Scene("cornell box", sceneWidth, sceneHeight, cam, spheres));


static Camera *pro = new ProjectiveCamera(Vec(0, 0, 0), \
																					Vec(0, 0, -1), \
																					Vec(0, 1.0, 0), \
																					5, 250, \
																					sceneWidth, sceneHeight);

static std::vector<Object *> sequence = {
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

Scene Scene::DepthOfField(Scene("depth of field", sceneWidth, sceneHeight, pro, sequence));
