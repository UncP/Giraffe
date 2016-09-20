/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:47:20
**/

#ifndef _NOISE_TEXTURE_HPP_
#define _NOISE_TEXTURE_HPP_

#include "../core/texture.hpp"

namespace Giraffe {

class NoiseTexture : public Texture
{
	public:
		NoiseTexture(const Vector3d &color1, const Vector3d &color2, const double &frequency = 0.1,
									bool emit = false, REFL refl = kDiffuse)
		:Texture(refl, emit), color1_(color1), color2_(color2), frequency_(frequency) { }

		Vector3d evaluate(IntersectionInfo &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		double   frequency_;
};

} // namespace Giraffe

#endif /* _NOISE_TEXTURE_HPP_ */