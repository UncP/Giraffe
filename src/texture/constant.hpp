/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:41:13
**/

#ifndef _CONSTANT_TEXTURE_HPP_
#define _CONSTANT_TEXTURE_HPP_

#include "../core/texture.hpp"

namespace Giraffe {

class ConstantTexture : public Texture
{
	public:
		ConstantTexture(const Vector3d &color, REFL refl)
		:Texture(refl), color_(color) { }

		Vector3d evaluate(const Vertex &vertex) const override {
			return color_;
		}

	private:
		Vector3d color_;
};

} // namespace Giraffe

#endif /* _CONSTANT_TEXTURE_HPP_ */