/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:53:39
**/

#ifndef _BUMP_BRICK_TEXTURE_HPP_
#define _BUMP_BRICK_TEXTURE_HPP_

#include "../core/texture.hpp"

namespace Giraffe {

class BumpBrickTexture : public Texture
{
	public:
		static const int map_len = 100;

		BumpBrickTexture(	const Vector3d &color1, const Vector3d &color2,
											double width, double height, double interval, double gradient);

		Vector3d evaluate(Vertex &vertex) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		double   width_;
		double 	 height_;
		double   wf_;
		double   hf_;
		double   gradient_;

		char     height_map_[map_len * map_len];

		void generateHeightMap();
		void showHeightMap();
};

} // namespace Giraffe

#endif /* _BUMP_BRICK_TEXTURE_HPP_ */