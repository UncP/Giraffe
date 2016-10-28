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

void Scene::accelerate(int beg, int end)
{
	BVH *bvh = new BVH();
	bvh->build(objects_.begin() + beg, objects_.begin() + end);
	objects_.erase(objects_.begin() + beg, objects_.begin() + end);
	objects_.push_back(static_cast<Object *>(bvh));
	accelerate_ = true;
}

} // namespace Giraffe
