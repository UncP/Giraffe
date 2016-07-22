/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Link:     https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-06-25 18:23:39
**/

#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <fstream>
#include <cstring>
#include <memory>

#include "vector.hpp"

class Canvas
{
	public:
		Canvas(uint32_t *pixels, const int width, const int height)
			:pixels_(pixels), width_(width), height_(height) {
				memset(pixels_, 0, sizeof(uint32_t) * width_ * height_);
		}

		void save(const char *file) const {
			std::ofstream out(file, std::ios::out | std::ios::binary);
			if (!out) { std::cerr << "文件打开失败 :(\n"; return ; }
			out << "P6\n" << width_ << " " << height_ << "\n255\n";
			for (int i = 0, end = width_ * height_; i < end; ++i) {
				Color c(pixels_[i]);
				out << static_cast<uint8_t>(std::min(1.0, c.r_) * 255.0) <<
							 static_cast<uint8_t>(std::min(1.0, c.g_) * 255.0) <<
							 static_cast<uint8_t>(std::min(1.0, c.b_) * 255.0);
			}
			out.close();
		}

		void putPixel(const int x, const int y, const Color &c) {
			if (x >= 0 && x < width_ && y >=0 && y < height_)
				pixels_[x + width_ * y] = c.uint();
		}

		Canvas(const Canvas &) = delete;
		Canvas& operator=(const Canvas &) = delete;

		~Canvas() { }

	private:
		uint32_t *pixels_;
		int 			width_;
		int 			height_;
};

#endif /* _CANVAS_H_ */