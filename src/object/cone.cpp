/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-05 22:37:04
**/

#include "cone.hpp"

namespace Giraffe {

bool Cone::intersect(const Ray &ray, Isect &isect) const
{
	// 计算光线与底面的交点 dot((o + t * d - c), axis) = 0
	double dis = -dot(ray.origin() - center_, axis_) / dot(ray.direction(), axis_);
	if (dis < 0) return false;

	Vector3d hitPos = ray.origin() + dis * ray.direction();

}

} // namespace Giraffe
