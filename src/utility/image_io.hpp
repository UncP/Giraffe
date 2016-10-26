/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-26 17:06:03
**/

#ifndef _IMAGE_IO_HPP_
#define _IMAGE_IO_HPP_

#include <string>

#include "../math/vector.hpp"

namespace Giraffe {

class ImageIO
{
	public:
		ImageIO() { }

		static bool save_png(int width, int height, const Vector3d *pixels, std::string &file);

		static bool read_png(const char *file, int &width, int &height, Vector3d* &image);

		static bool save_ppm(int width, int height, const Vector3d *pixels, std::string &file);

	private:
		static std::string generate_file_name();
};

} // namespace Giraffe

#endif /* _IMAGE_IO_HPP_ */