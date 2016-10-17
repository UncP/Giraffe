/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:50:18
**/

#ifndef _BRICK_TEXTURE_HPP_
#define _BRICK_TEXTURE_HPP_

#include "../math/matrix.hpp"
#include "../core/texture.hpp"

namespace Giraffe {

class BrickTexture : public Texture
{
	public:
		BrickTexture(	const Vector3d &color1, const Vector3d &color2, double width, double height,
									double interval, const Matrix2 &transform = Matrix2::Identity,
									bool emit = false, REFL refl = kDiffuse)
		:Texture(refl, emit), color1_(color1), color2_(color2), transform_(transform) {
			width_  = width + interval;
			height_ = height + interval;
			wf_ = (interval * 0.5) / width;
			hf_ = (interval * 0.5) / height;
		}

		Vector3d evaluate(IntersectionInfo &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		double   width_;
		double 	 height_;
		double   wf_;
		double   hf_;
		Matrix2  transform_;
};

} // namespace Giraffe

#endif /* _BRICK_TEXTURE_HPP_ */