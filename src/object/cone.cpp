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
	double ad = dot(ray.direction(), axis_);
	double dis = -dot(ray.origin() - center_, axis_) / ad;
	if (dis < 0) return false;

	Point3d hitPos = ray.origin() + dis * ray.direction();

	// 与底面相交
	if (ad > 0 && (hitPos - center_).length2() < radius2_ && dis < isect.distance()) {
		isect.update(dis, this, hitPos, -axis_, Point2d(), material_);
		return true;
	}


	return false;
}

} // namespace Giraffe
