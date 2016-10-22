/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-07-30 17:18:13
**/

#include <unistd.h>

#include "window.hpp"

namespace Giraffe {

Window::Window(const std::string &title, const int width, const int height)
:title_(title), width_(width), height_(height), pixels_(new Vector3d[width_*height_]),
 canvas_(new uint32_t[width_*height_]) {

}

void Window::ray_tracing(const Scene &scene, const int &samples)
{
	const Camera &camera = scene.camera();
	const std::vector<Object *> &objects = scene.objects();
	const std::vector<Light *> &lights = scene.lights();
	double inv = 1.0 / samples;
	Vector3d color;
	auto beg = std::chrono::high_resolution_clock::now();
	#pragma omp parallel for schedule(dynamic, 1) private(color)
	for (int x = 0; x < width_; ++x) {
		fprintf(stderr,"\rprogress: %5.2f%%", 100 * (x / static_cast<float>(width_-1)));
		for (int y = 0; y < height_; ++y) {
			for (int sx = 0, i = x + y * width_; sx < 2; ++sx) {
				for (int sy = 0; sy < 2; ++sy, color = Vector3d()) {
					for (int n = 0; n < samples; ++n) {
						double a = Random(), b = Random();
						Point2d sample((x+(a+sx+0.5)*0.5)/width_, (y+(b+sy+0.5)*0.5)/height_);
						Ray ray = camera.generateRay(sample);
						color += PathTracer::trace(ray, objects, lights, 0) * inv;
					}
					pixels_[i] += color * 0.25;
				}
			}
		}
	}

	auto end  = std::chrono::high_resolution_clock::now();
	auto Time = std::chrono::duration<double, std::ratio<1>>(end - beg).count();
	std::cerr << "\ntime: " << std::setw(8) << Time << "  s\n";

	save_png();
}

void Window::save_ppm() const
{
	time_t t;
	struct tm *tt;
	time(&t);
	tt = localtime(&t);
	char file[32];
	snprintf(file, 32, "%d-%d-%d", tt->tm_hour, tt->tm_min, tt->tm_sec);
	strcat(file, ".ppm");
	std::ofstream out(file, std::ios::out | std::ios::binary);
	if (!out) { std::cerr << "ppm格式图片保存失败 :(\n"; return ; }
	out << "P3\n" << width_ << " " << height_ << "\n255\n";
	for (int i = 0, end = width_ * height_; i < end; ++i) {
		int r = static_cast<int>(std::pow(std::min(pixels_[i].x_,1.0),1 / 2.2) * 255 + 0.5);
		int g = static_cast<int>(std::pow(std::min(pixels_[i].y_,1.0),1 / 2.2) * 255 + 0.5);
		int b = static_cast<int>(std::pow(std::min(pixels_[i].z_,1.0),1 / 2.2) * 255 + 0.5);
		out << r << " " << g << " " << b << " ";
	}
	out.close();
}

bool Window::save_png() const
{
	time_t t;
	struct tm *tt;
	time(&t);
	tt = localtime(&t);
	char file[32];
	snprintf(file, 32, "%d-%d-%d", tt->tm_hour, tt->tm_min, tt->tm_sec);
	strcat(file, ".png");
	std::cerr << "save to: " << file << std::endl;

	FILE *fp = fopen(file, "wb");
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

	png_set_IHDR(png_ptr, info_ptr, width_, height_, 8, PNG_COLOR_TYPE_RGB_ALPHA,
	  PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);
	png_set_flush(png_ptr, 10);

	unsigned char *pic = new unsigned char[height_ * width_ * 4];
	if (!pic) {
		std::cerr << "png格式图片保存失败 :(\n";
		return false;
	}

	for (int i = 0, end = width_ * height_; i < end; ++i) {
		canvas_[i] = 0;
		canvas_[i] |= 0xFF << 24;
		canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].z_, 1.0) * 255.0) << 16;
		canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].y_, 1.0) * 255.0) << 8;
		canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].x_, 1.0) * 255.0);
	}

	memcpy(pic, static_cast<void *>(canvas_), height_ * width_ * 4);
	png_bytep *row_pointers = new png_bytep[height_];
	if (!row_pointers) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		std::cerr << "png格式图片保存失败 :(\n";
		return false;
	}
	for (int y = 0; y < height_; ++y)
		row_pointers[y] = static_cast<png_byte *>(pic + y * width_ * 4);
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, info_ptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	show_png(file);
	delete [] row_pointers;
	delete [] pic;
	return true;
}

void Window::show_png(const char *file) const
{
	// execlp("eog", "eog", file, NULL);
	execlp("subl", "subl", file, NULL);
}

} // namespace Giraffe
