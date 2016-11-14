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

Vector3d DirectionalLight::illuminate(Isect &dis) const
{
	return direction_;
}

Vector3d DirectionalLight::radiance(const Isect &isect) const
{
	return intensity_;
}

std::shared_ptr<Light> createDirectionalLight(Slice &slice)
{
	Vector3d direction = slice.findVector();
	Vector3d intensity = slice.findVector();
	assert(slice.eof());
	return std::shared_ptr<Light>(new DirectionalLight(direction, intensity));
}

} // namespace Giraffe
