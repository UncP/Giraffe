/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 17:29:00
**/

#include "plane.hpp"

namespace Giraffe {

bool Plane::hit(const Ray &ray, const double &distance, const Object *obj) const
{
	double a = dot(normal_, ray.direction());
	if (a > 0) return false;

	double b = -dot(ray.origin() - position_, normal_);

	double dis = b / a;

	if (dis > 0 && dis < distance && this != obj) return true;
	return false;
}

bool Plane::intersect(const Ray &ray, Isect &isect) const
{
	// (o + t * d - p) * n = 0;

	double a = dot(normal_, ray.direction());
	if (a > 0) return false;

	double b = -dot(ray.origin() - position_, normal_);

	double dis = b / a;

	if (dis > 0 && dis < isect.distance()) {
		Point3d hitPos(ray.origin() + ray.direction() * dis);
		isect.update(dis, this, hitPos, normal_, Point2d(), material_);
		return true;
	}
	return false;
}

} // namespace Giraffe
