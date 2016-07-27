/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-24 15:48:13
**/

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <fstream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <png.h>

#include "ray.hpp"
#include "camera.hpp"

class Window
{
	public:
		Window() = default;
		Window(const int width, const int height, const char *title)
			:width_(width), height_(height), pixels_(new Vec3[width_*height_]) {
			if (!pixels_) {
				std::cerr << "颜色初始化失败 :(\n";
				exit(-1);
			}

			if (SDL_Init(SDL_INIT_VIDEO)) {
				std::cerr << "SDL_Init failed :(\n";
				exit(-1);
			}

			screen_ = SDL_SetVideoMode(width_, height_, 32, SDL_SWSURFACE);
			if (!screen_) {
				SDL_Quit();
				std::cerr << "SDL_SetVideoMode failed :(\n";
				exit(-1);
			}
			canvas_ = static_cast<uint32_t *>(screen_->pixels);

			SDL_WM_SetCaption(title, NULL);
		}

		void render(const Scene &scene, const int &samples) {
			const Camera &camera = scene.camera();
			const std::vector<Sphere *> &spheres = scene.sphere();
			double inv = 1.0 / samples;
			Vec3 color;
			#pragma omp parallel for schedule(dynamic, 1) private(color)
			for (int x = 0; x < width_; ++x) {
				fprintf(stderr,"\rprogress: %5.2f%%", 100 * (x / static_cast<float>(width_-1)));
				for (int y = 0; y < height_; ++y) {
					for (int sx = 0, i = x + (height_ - 1 - y) * width_; sx < 2; ++sx) {
						for (int sy = 0; sy < 2; ++sy, color = Vec3()) {
							for (int n = 0; n < samples; ++n) {
								Ray ray;
								camera.computeRay(width_, height_, sx, sy, x, y, ray);
								color += ray.trace(spheres, 0) * inv;
							}
							pixels_[i] += color * 0.25;
						}
					}
				}
			}
		}

		void show() const {
			for (int i = 0, end = width_ * height_; i < end; ++i) {
				canvas_[i] = 0;
				canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].x_, 1.0) * 255.0) << 16;
				canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].y_, 1.0) * 255.0) << 8;
				canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].z_, 1.0) * 255.0);
			}
			SDL_UpdateRect(screen_, 0, 0, 0, 0);
		}

		void save_ppm(const char *file) const {
			std::ofstream out(file, std::ios::out | std::ios::binary);
			if (!out) { std::cerr << "文件打开失败 :(\n"; return ; }
			out << "P3\n" << width_ << " " << height_ << "\n255\n";
			for (int i = 0, end = width_ * height_; i < end; ++i) {
				int r = static_cast<int>(std::pow(std::min(pixels_[i].x_,1.0),1 / 2.2) * 255 + 0.5);
				int g = static_cast<int>(std::pow(std::min(pixels_[i].y_,1.0),1 / 2.2) * 255 + 0.5);
				int b = static_cast<int>(std::pow(std::min(pixels_[i].z_,1.0),1 / 2.2) * 255 + 0.5);
				out << r << " " << g << " " << b << " ";
			}
			out.close();
		}

		bool save_png(const char *file) const {
			FILE *fp = fopen(file, "wb");
			if (!fp) return false;

			png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
			if (!png_ptr) {
				fclose(fp);
				return false;
			}
			png_infop info_ptr = png_create_info_struct(png_ptr);
			if (!info_ptr) {
				png_destroy_write_struct(&png_ptr, (png_infopp) 0);
				fclose(fp);
				return false;
			}

			if (setjmp(png_jmpbuf(png_ptr))) {
				png_destroy_write_struct(&png_ptr, &info_ptr);
				fclose(fp);
				return false;
			}

			png_init_io(png_ptr, fp);

			png_set_IHDR(png_ptr, info_ptr, width_, height_, 8, PNG_COLOR_TYPE_RGB_ALPHA,
			  PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
			png_write_info(png_ptr, info_ptr);
			png_set_flush(png_ptr, 10);

			unsigned char *pic = new unsigned char[height_ * width_ * 4];
			memcpy(pic, static_cast<void *>(canvas_), height_ * width_ * 4);
			png_bytep *row_pointers = new png_bytep[height_];
			if (!pic || !row_pointers) {
				png_destroy_write_struct(&png_ptr, &info_ptr);
				return false;
			}
			for (int y = 0; y < height_; ++y)
				row_pointers[y] = static_cast<png_byte *>(pic + (height_ - 1 - y) * width_ * 4);
			png_write_image(png_ptr, row_pointers);
			png_write_end(png_ptr, info_ptr);

			png_destroy_write_struct(&png_ptr, &info_ptr);
			fclose(fp);
			delete [] row_pointers;
			delete [] pic;
			return true;
		}

		Window& operator=(const Window &) = delete;

		~Window() { delete [] pixels_; }
	private:
		int 				 width_;
		int					 height_;
		Vec3				*pixels_;
		uint32_t		*canvas_;
		SDL_Surface *screen_;
};

#endif /* _WINDOW_H_ */