/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-27 21:01:11
**/

#include "scene.hpp"

const int sceneWidth = 1024, sceneHeight = 768;
static Camera *cam = new PerspectiveCamera(	Vec(0.0, 0.0, 0.0), 	\
																						Vec(0.0, -0.08, -1.0),\
																						Vec(0.0, 1.0, 0.0),		\
																						sceneWidth, sceneHeight);
static std::vector<Sphere *> spheres = {
	new Sphere(Vec(0.0, 1e5-40, -250.0), 1e5, 	Vec(0.75)),
	new Sphere(Vec(0.0, 1e5+40, -250.0), 1e5, 	Vec(0.75)),
	new Sphere(Vec(0.0, 0.0, -1e5-300), 	1e5, 	Vec(0.75)),
	new Sphere(Vec(0.0, 0.0, 1e5), 			1e5, 		Vec(0.0)),
	new Sphere(Vec(-1e5-50, 0.0, -250.0),1e5, 	Vec(0.75, 0.25, 0.25)),
	new Sphere(Vec(1e5+50, 0.0, -250.0), 1e5, 	Vec(0.25, 0.75, 0.25)),
	new Sphere(Vec(-20.0, -24.5, -255.0),15.5,	Vec(0.999), 		Vec(), 		kReflect),
	new Sphere(Vec(25.0, -26.5, -215.0), 13.5,	Vec(0.999), 		Vec(), 		kRefract),
	new Sphere(Vec(0.0, 839.8, -225.0), 	800, 	Vec(1.0), 			Vec(8, 8, 8))
};

Scene Scene::CornellBox(Scene("cornell box", sceneWidth, sceneHeight, cam, spheres));

static Camera *pro = new ProjectiveCamera(Vec(0.0, 0.0, 0.0), \
																					Vec(0.0, 0.0, -1), \
																					Vec(0.0, 1.0, 0.0), \
																					3, 250);

static std::vector<Sphere *> sequence = {
	new Sphere(Vec(-40.0, 0.0, -230.0), 20, 	Vec(1.0, 0.0, 0.0)),
	new Sphere(Vec(-20.0, 0.0, -220.0), 20, 	Vec(1.0, 0.0, 0.0)),
	new Sphere(Vec(	0.0, 0.0,  -200.0), 20, 	Vec(1.0, 0.0, 0.0)),
	new Sphere(Vec(	20.0, 0.0, -180.0), 20, 		Vec(1.0, 0.0, 0.0)),
	new Sphere(Vec(	40.0, 0.0, -170.0), 20, 		Vec(1.0, 0.0, 0.0)),
	new Sphere(Vec(0.0, 0, -1e5-250), 1e5, Vec(0.75)),
	new Sphere(Vec(0.0, -1e5-20, 0), 1e5, Vec(0.75)),
	new Sphere(Vec(0.0, 109.0, -200.0), 10, 	Vec(1.0), Vec(8, 8, 8))
};

Scene Scene::DepthOfField(Scene("depth of field", 512, 512, pro, sequence));
