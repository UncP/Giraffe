/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:51:50
**/

#ifndef _IMAGE_TEXTURE_HPP_
#define _IMAGE_TEXTURE_HPP_

#include <png.h>
#include <cassert>

#include "../core/texture.hpp"
#include "../utility/image_io.hpp"

namespace Giraffe {

class ImageTexture : public Texture
{
	public:
		ImageTexture(const char *name, double frequency):frequency_(frequency) {
			assert(ImageIO::read_png(name, width_, height_, image_));
		}

		~ImageTexture() { delete [] image_; }

		Vector3d evaluate(const Vertex &vertex) const override;

	private:
		int       width_, height_;
		double    frequency_;
		Vector3d *image_;
};

} // namespace Giraffe

#endif /* _IMAGE_TEXTURE_HPP_ */