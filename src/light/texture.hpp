/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-21 13:47:42
**/

#ifndef _TEXTURE_LIGHT_HPP_
#define _TEXTURE_LIGHT_HPP_

#include <memory>

#include "../core/light.hpp"

namespace Giraffe {

class TextureLight : public Light
{
	public:
		TextureLight(const std::shared_ptr<Texture> texture, const Vector3d &intensity);

		Vector3d computeLight(Isect &isect) const override;

		Vector3d illuminate(const Isect &isect) const override;

	private:

		using Light::intensity_;

		const std::shared_ptr<Texture> texture_;
};

} // namespace Giraffe

#endif /* _TEXTURE_LIGHT_HPP_ */