/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-23 11:09:50
**/

#include "triangle.hpp"

namespace Giraffe {

bool Triangle::intersect(const Ray &ray, Isect &isect) const
{
	Vector3d a_b	(a_ - b_);
	Vector3d a_c	(a_ - c_);
	Vector3d a_pos(a_ - ray.origin());

	Vector3d a_bCross_a_pos(cross(a_b, a_pos));
	Vector3d a_cCross_dir	 (cross(a_c, ray.direction()));

	double m = 1.0 / dot(a_b, a_cCross_dir);

	double t = dot(a_c, a_bCross_a_pos) * (-m);
	if (t < kEpsilon) return false;

	double u = dot(a_pos, a_cCross_dir) * m;
	if (u < 0.0 || u > 1.0) return false;

	double v = dot(ray.direction(), a_bCross_a_pos) * m;
	if (v < 0.0 || v > (1.0 - u)) return false;

	if (t < isect.distance()) {
		Point3d hitPos(ray.origin() + ray.direction() * t);
		isect.update(t, IntersectionInfo(hitPos, Point2d(u, v), normal_), texture_.get());
		return true;
	} else {
		return false;
	}
}

} // namespace Giraffe
