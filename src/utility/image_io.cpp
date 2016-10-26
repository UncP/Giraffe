/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-26 17:06:33
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <png.h>

#include "image_io.hpp"

namespace Giraffe {

std::string ImageIO::generate_file_name()
{
	time_t t;
	struct tm *tt;
	time(&t);
	tt = localtime(&t);
	std::ostringstream file;
	file << tt->tm_hour << "-" << tt->tm_min << "-" << tt->tm_sec;
	return file.str();
}

bool ImageIO::save_png(int width, int height, const Vector3d *pixels, std::string &file)
{
	file = generate_file_name();
	file += ".png";
	std::cerr << "save to: " << file << std::endl;

	FILE *fp = fopen(file.c_str(), "wb");
	if (!fp) {
		std::cerr << "文件打开失败 :(\n";
		return false;
	}

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if (!png_ptr) {
		std::cerr << "png格式图片保存失败 :(\n";
		fclose(fp);
		return false;
	}
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, (png_infopp) 0);
		std::cerr << "png格式图片保存失败 :(\n";
		fclose(fp);
		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		std::cerr << "png格式图片保存失败 :(\n";
		fclose(fp);
		return false;
	}

	png_init_io(png_ptr, fp);

	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA,
	  PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);
	png_set_flush(png_ptr, 10);

	unsigned char pic[height * width * 4];
	uint32_t canvas[width * height];
	for (int i = 0, end = width * height; i < end; ++i) {
		canvas[i] = 0;
		canvas[i] |= 0xFF << 24;
		canvas[i] |= static_cast<uint8_t>(std::min(pixels[i].z_, 1.0) * 255.0) << 16;
		canvas[i] |= static_cast<uint8_t>(std::min(pixels[i].y_, 1.0) * 255.0) << 8;
		canvas[i] |= static_cast<uint8_t>(std::min(pixels[i].x_, 1.0) * 255.0);
	}

	memcpy(pic, static_cast<void *>(canvas), height * width * 4);
	png_bytep row_pointers[height];

	for (int y = 0; y < height; ++y)
		row_pointers[y] = static_cast<png_byte *>(pic + y * width * 4);
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, info_ptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);

	fclose(fp);
	return true;
}

bool ImageIO::read_png(const char *file, int &width, int &height, Vector3d* &image)
{
	FILE *fp = fopen(file, "rb");
	if (!fp) {
		std::cerr << "无法打开文件 " << file << std::endl;
		return false;
	}

	const size_t HEADER_LENGTH = 8;
	png_byte header[HEADER_LENGTH];
	size_t n = fread(header, 1, HEADER_LENGTH, fp);
	if (n != HEADER_LENGTH || png_sig_cmp(header, 0, HEADER_LENGTH)) {
		std::cerr << "png图像载入失败 :(\n";
		return false;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if (!png_ptr) {
		fclose(fp);
		std::cerr << "png图像载入失败 :(\n";
		return false;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp) 0, (png_infopp) 0);
		fclose(fp);
		std::cerr << "png图像载入失败 :(\n";
		return false;
	}

	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info) {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)0);
		fclose(fp);
		std::cerr << "png图像载入失败 :(\n";
		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		std::cerr << "png图像载入失败 :(\n";
		return false;
	}

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, HEADER_LENGTH);

	png_read_info(png_ptr, info_ptr);
	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
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

	if ((int)png_get_rowbytes(png_ptr, info_ptr) != (width * 4)) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		std::cerr << "png图像载入失败 :(\n";
		return false;
	}

	unsigned char buffer[width * height * 4];
	png_bytep row_pointers[height];

	for (int y = 0; y < height; ++y)
		row_pointers[y] = (png_byte *)(buffer + y * width * 4);
	png_read_rows(png_ptr, row_pointers, 0, height);

	image = new Vector3d[width * height];

	for (int i = 0; i != width * height; ++i) {
		int off = i * 4;
		int x = static_cast<int>(buffer[off]);
		image[i].x_ = static_cast<double>(x) / 255.0;
		int y = static_cast<int>(buffer[off+1]);
		image[i].y_ = static_cast<double>(y) / 255.0;
		int z = static_cast<int>(buffer[off+2]);
		image[i].z_ = static_cast<double>(z) / 255.0;
	}

	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	fclose(fp);
	return true;
}

bool ImageIO::save_ppm(int width, int height, const Vector3d *pixels, std::string &file)
{
	file = generate_file_name();
	file += ".ppm";

	std::ofstream out(file, std::ios::out | std::ios::binary);
	if (!out) { std::cerr << "ppm格式图片保存失败 :(\n"; return false; }
	out << "P3\n" << width << " " << height << "\n255\n";
	for (int i = 0, end = width * height; i < end; ++i) {
		int r = static_cast<int>(std::pow(std::min(pixels[i].x_,1.0),1 / 2.2) * 255 + 0.5);
		int g = static_cast<int>(std::pow(std::min(pixels[i].y_,1.0),1 / 2.2) * 255 + 0.5);
		int b = static_cast<int>(std::pow(std::min(pixels[i].z_,1.0),1 / 2.2) * 255 + 0.5);
		out << r << " " << g << " " << b << " ";
	}
	out.close();
	return true;
}

} // namespace Giraffe
