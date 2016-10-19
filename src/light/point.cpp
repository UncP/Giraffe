/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-18 18:32:12
**/

#include "point.hpp"

namespace Giraffe {

Vector3d PointLight::illuminate(const Isect &isect) const
{
	Vector3d direction(position_ - isect.position());

	return intensity_ * (1.0 / direction.length2());
}

Vector3d PointLight::computeLight(const Point3d &position, const Vector3d &normal) const
{
	return normalize(position_ - position);
}

} // namespace Giraffe
