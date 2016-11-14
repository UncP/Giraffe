/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-10 22:43:04
**/

#ifndef _SPOT_TEXTURE_HPP_
#define _SPOT_TEXTURE_HPP_

#include "../core/texture.hpp"

namespace Giraffe {

class SpotTexture : public Texture
{
	public:
		SpotTexture(const Vector3d &color1, const Vector3d &color2, double radius)
		:color1_(color1), color2_(color2), radius_(radius) { }

		Vector3d evaluate(Vertex &vertex) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		double   radius_;
};

std::shared_ptr<Texture> createSpotTexture(Slice &slice);

} // namespace Giaffe

#endif /* _SPOT_TEXTURE_HPP_ */