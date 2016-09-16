/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-19 01:44:58
**/

#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <ctime>
#include <random>
#include <png.h>
#include <assert.h>

#include "../math/constant.hpp"
#include "../math/point.hpp"
#include "../math/vector.hpp"
#include "../math/vertex.hpp"

namespace Giraffe {

class Noise
{
	public:

		constexpr static int PerlinNumber = 256;
		constexpr static int Mask = PerlinNumber - 1;

		Noise();

		int index(int, int, int) const;

		double gnoise(const Point3d &) const;

		double turbulence(const Point3d &) const;

		double fractalSum(const Point3d &) const;

		double glattice(int, int, int, double, double, double) const;

	private:
		int     octaves_;
		int     permutationTable_[2 * PerlinNumber];
		double  gradientTable_[3 * PerlinNumber];
};

class Texture
{
	public:
		Texture():refl_(kDiffuse), emit_(false) { }

		Texture(REFL refl, bool emit):refl_(refl), emit_(emit) { }

		virtual Vector3d evaluate(Vertex &) const = 0;

		REFL refl() const { return refl_; }

		Vector3d color(Vertex &v) const {
			return !emit_ ? evaluate(v) : Vector3d();
		}

		Vector3d emission(Vertex &v) const {
			return emit_ ? evaluate(v) : Vector3d();
		}

		virtual ~Texture() { }

	protected:
		REFL      refl_;
		bool      emit_;
};

class ConstantTexture : public Texture
{
	public:
		ConstantTexture(const Vector3d &color, bool emit = false, REFL refl = kDiffuse)
		:Texture(refl, emit), color_(color) { }

		Vector3d evaluate(Vertex &) const override { return color_; }

	private:
		Vector3d color_;
};

class StripeTexture : public Texture
{
	public:
		StripeTexture(const Vector3d &color1, const Vector3d &color2, int axis,
									const double &factor = 1.0, bool emit = false, REFL refl = kDiffuse)
		:Texture(refl, emit), color1_(color1), color2_(color2), axis_(axis),
		 factor_(1.0 / factor) { }

		Vector3d evaluate(Vertex &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		int      axis_;
		double 	 factor_;
};

class NoiseTexture : public Texture
{
	public:
		NoiseTexture(const Vector3d &color1, const Vector3d &color2, const double &frequency = 0.1,
									bool emit = false, REFL refl = kDiffuse)
		:Texture(refl, emit), color1_(color1), color2_(color2), frequency_(frequency) { }

		Vector3d evaluate(Vertex &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		double   frequency_;
};

class MarbleTexture : public Texture
{
	public:
		MarbleTexture(const Vector3d &color1, const Vector3d &color2, const Vector3d &color3,
									double frequency = 0.1, bool emit = false, REFL refl = kDiffuse)
		:Texture(refl, emit), color1_(color1), color2_(color2), color3_(color3),
		 frequency_(frequency) { }

	Vector3d evaluate(Vertex &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		Vector3d color3_;
		double   frequency_;
};

class BrickTexture : public Texture
{
	public:
		BrickTexture(	const Vector3d &color1, const Vector3d &color2, double width, double height,
									double interval, bool emit = false, REFL refl = kDiffuse)
		:Texture(refl, emit), color1_(color1), color2_(color2) {
			width_  = width + interval;
			height_ = height + interval;
			wf_ = (interval * 0.5) / width;
			hf_ = (interval * 0.5) / height;
		}

		Vector3d evaluate(Vertex &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		double   width_;
		double 	 height_;
		double   wf_;
		double   hf_;
};

class ImageTexture : public Texture
{
	public:
		ImageTexture(const char *name, double frequency = 0.01, bool emit=false, REFL refl=kDiffuse)
		:Texture(refl, emit), frequency_(frequency) {
			FILE *fp = fopen(name, "rb");
			if (!fp) {
				std::cerr << "无法打开文件 " << name << std::endl;
				return ;
			}

			const size_t HEADER_LENGTH = 8;
			png_byte header[HEADER_LENGTH];
			size_t n = fread(header, 1, HEADER_LENGTH, fp);
			if (n != HEADER_LENGTH || png_sig_cmp(header, 0, HEADER_LENGTH)) {
				std::cerr << "png图像载入失败 :(\n";
				return ;
			}

			png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
			if (!png_ptr) {
				fclose(fp);
				std::cerr << "png图像载入失败 :(\n";
				return ;
			}

			png_infop info_ptr = png_create_info_struct(png_ptr);
			if (!info_ptr) {
				png_destroy_read_struct(&png_ptr, (png_infopp) 0, (png_infopp) 0);
				fclose(fp);
				std::cerr << "png图像载入失败 :(\n";
				return ;
			}

			png_infop end_info = png_create_info_struct(png_ptr);
			if (!end_info) {
				png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)0);
				fclose(fp);
				std::cerr << "png图像载入失败 :(\n";
				return ;
			}

			if (setjmp(png_jmpbuf(png_ptr))) {
				png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
				fclose(fp);
				std::cerr << "png图像载入失败 :(\n";
				return ;
			}

			png_init_io(png_ptr, fp);
			png_set_sig_bytes(png_ptr, HEADER_LENGTH);

			png_read_info(png_ptr, info_ptr);
			width_ = png_get_image_width(png_ptr, info_ptr);
			height_ = png_get_image_height(png_ptr, info_ptr);
			int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
			png_byte color_type = png_get_color_type(png_ptr, info_ptr);

			if (color_type != PNG_COLOR_TYPE_RGBA)
				png_set_expand(png_ptr);
			if (color_type == PNG_COLOR_TYPE_GRAY ||
			  color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
				png_set_gray_to_rgb(png_ptr);
			if (bit_depth < 8)
				png_set_packing(png_ptr);
			else if (bit_depth == 16)
				png_set_strip_16(png_ptr);
			if (color_type != PNG_COLOR_TYPE_RGBA)
				png_set_filler(png_ptr, 255, PNG_FILLER_AFTER);
			png_read_update_info(png_ptr, info_ptr);

			if ((int)png_get_rowbytes(png_ptr, info_ptr) != (width_ * 4)) {
				png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
				fclose(fp);
				std::cerr << "png图像载入失败 :(\n";
				return ;
			}

			unsigned char *buffer = new unsigned char[width_ * height_ * 4];
			png_bytep *row_pointers = new png_bytep[height_];
			for (int y = 0; y < height_; ++y)
				row_pointers[y] = (png_byte *)(buffer + y * width_ * 4);
			png_read_rows(png_ptr, row_pointers, 0, (long unsigned int)height_);

			image_ = new Vector3d[width_ * height_];

			for (int i = 0; i != width_ * height_; ++i) {
				int off = i * 4;
				int x = static_cast<int>(buffer[off]);
				image_[i].x_ = static_cast<double>(x) / 255.0;
				int y = static_cast<int>(buffer[off+1]);
				image_[i].y_ = static_cast<double>(y) / 255.0;
				int z = static_cast<int>(buffer[off+2]);
				image_[i].z_ = static_cast<double>(z) / 255.0;
			}

			delete [] row_pointers;
			delete [] buffer;
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			fclose(fp);
		}

		~ImageTexture() { delete [] image_; }

		Vector3d evaluate(Vertex &) const override;

	private:
		int       width_, height_;
		double    frequency_;
		Vector3d *image_;
};

class BumpBrickTexture : public Texture
{
	public:

		static const int map_len = 100;

		BumpBrickTexture(	const Vector3d &color1, const Vector3d &color2,
											double width, double height,
											double interval, bool emit = false, REFL refl = kDiffuse)
		:Texture(refl, emit), color1_(color1), color2_(color2) {
			assert(width > 0 && height > 0 && interval > 0);
			width_  = width + interval;
			height_ = height + interval;
			wf_ = (interval * 0.5) / width;
			hf_ = (interval * 0.5) / height;
			generateHeightMap();
		}

		Vector3d evaluate(Vertex &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		double   width_;
		double 	 height_;
		double   wf_;
		double   hf_;
		unsigned char height_map_[map_len * map_len];

		void generateHeightMap();
};

} // namespace Giraffe

#endif /* _TEXTURE_HPP_ */