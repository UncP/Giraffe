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
#include <SDL/SDL.h>

#include "ray.hpp"

using std::vector;

class Window
{
	public:
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

		void rayTrace(const Vec3 &origin, const double &fov, const vector<Light *> &light,
									const vector<Sphere *> &spheres) {
			double fac = tan(fov * PI / 360.0);
#pragma omp parallel for schedule(dynamic, 1)
			for (int x = 0; x < width_; ++x) {
				fprintf(stderr,"\r%5.2f%%", 100 * (x / static_cast<float>(width_-1)));
				for (int y = 0; y < height_; ++y) {
					Vec3 dir((2*((x+0.5)/width_)-1)*fac, (1-2*((y+0.5)/height_))*fac, -1);
					normalize(dir);
					int i = x + y * width_;
					pixels_[i] += Ray(origin, dir).trace(light, spheres, 0);
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
			SDL_UpdateRect(screen_, 0, 0, 0, 0); }

		void save(const char *file) const {
			std::ofstream out(file, std::ios::out | std::ios::binary);
			if (!out) { std::cerr << "文件打开失败 :(\n"; return ; }
			out << "P6\n" << width_ << " " << height_ << "\n255\n";
			for (int i = 0, end = width_ * height_; i < end; ++i) {
				uint8_t r = static_cast<uint32_t>(std::min(pixels_[i].x_, 1.0) * 255.0);
				uint8_t g = static_cast<uint32_t>(std::min(pixels_[i].y_, 1.0) * 255.0);
				uint8_t b = static_cast<uint32_t>(std::min(pixels_[i].z_, 1.0) * 255.0);
				out << r << g << b;
			}
			out.close();
		}

		Window(const Window &) = delete;
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