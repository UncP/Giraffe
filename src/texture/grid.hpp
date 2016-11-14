/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-08 11:38:19
**/

#ifndef _GRID_TEXTURE_HPP_
#define _GRID_TEXTURE_HPP_

#include "../math/matrix.hpp"
#include "../core/texture.hpp"

namespace Giraffe {

class GridTexture : public Texture
{
	public:
		GridTexture(const Vector3d &color1, const Vector3d &color2, int axis, const double factor,
			const Matrix &transform)
		:color1_(color1), color2_(color2), transform_(transform), factor_(factor) { }

		Vector3d evaluate(Vertex &vertex) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		Matrix   transform_;
		double 	 factor_;
};

std::shared_ptr<Texture> createGirdTexture(Slice &slice);

} // namespace Giraffe

#endif /* _GRID_TEXTURE_HPP_ */