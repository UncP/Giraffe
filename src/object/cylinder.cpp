/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-20 22:58:45
**/

#include "cylinder.hpp"

namespace Giraffe {

bool Cylinder::intersect(const Ray &ray, Isect &isect) const
{
	Vector3d ab(center1_ - ray.origin());
	Vector3d n(normalize(cross(axis_, ray.direction())));
	double dis = std::fabs(dot(ab, n));

	if (dis > radis_) return false;

	return false;
}

} // namespace Giraffe
