/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-28 18:19:27
**/

#include "disk.hpp"

namespace Giraffe {

bool Disk::intersect(const Ray &ray, Isect &isect) const
{
	double dis = dot(center_ - ray.origin(), axis_) / dot(axis_, ray.direction());
	if (dis < 0) return false;

	Point3d hitPos(ray.origin() + ray.direction() * dis);
	Vector3d v(hitPos - center_);
	double d = v.length2();
	if (d < radis2_min_ || d > radis2_max_) return false;

	if (dis < isect.distance()) {
		// double inv2radis = 1.0 / (2 * (radis1_ + radis2_));
		// Point2d uv((hitPos.x_-center_.x_+(radis1_+radis2_)) * inv2radis,
			// (hitPos.y_-center_.y_+(radis1_+radis2_)) * inv2radis);
		isect.update(dis, IntersectionInfo(hitPos, Point2d(), axis_), texture_.get());
		return true;
	}
	return false;
}

} // namespace Giraffe
