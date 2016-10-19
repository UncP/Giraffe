/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-07-27 21:01:11
**/

#include "scene.hpp"

namespace Giraffe {

void Scene::accelerate()
{
	BVH *bvh = new BVH();
	bvh->build(objects_);
	objects_.clear();
	objects_.push_back(static_cast<Object *>(bvh));
	accelerate_ = true;
}

Scene::~Scene()
{
	delete camera_;
	if (!accelerate_)
		std::for_each(objects_.begin(), objects_.end(), [](Object *obj) { delete obj; });
}

} // namespace Giraffe
