/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-21 13:47:50
**/

#include "texture.hpp"

namespace Giraffe {

TextureLight::TextureLight(const std::shared_ptr<Texture> texture, const Vector3d &intensity)
:Light(intensity), texture_(texture.get()) { }

Vector3d TextureLight::computeLight(Isect &isect) const
{
	return Vector3d(0);
}

Vector3d TextureLight::illuminate(const Isect &isect) const
{
	return Vector3d(0);
}


} // namespace Giraffe
