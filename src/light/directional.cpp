/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-19 18:51:47
**/

#include "directional.hpp"

namespace Giraffe {

DirectionalLight::DirectionalLight(const Vector3d &direction, const Vector3d &intensity)
:Light(intensity), direction_(-normalize(direction)) { }

Vector3d DirectionalLight::computeLight(Isect &dis) const
{
	return direction_;
}

Vector3d DirectionalLight::illuminate(const Isect &isect) const
{
	return intensity_;
}

} // namespace Giraffe
