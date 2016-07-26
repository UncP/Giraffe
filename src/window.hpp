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
#include "camera.hpp"

static const double fac = 0.5135;

static std::default_random_engine generator(time(0));
static std::uniform_real_distribution<double> distribution(0, 1);

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

		void rayTrace(const Camera &cam, const std::vector<Sphere *> &spheres, const int &samples) {
			Vec3 cx(width_ * fac / height_, 0, 0), cy(cross(cx, cam.direction_));
			normalize(cy);
			cy *= fac;
			Vec3 color;
			#pragma omp parallel for schedule(dynamic, 1) private(color)
			for (int x = 0; x < width_; ++x) {
				fprintf(stderr,"\rprogress: %5.2f%%", 100 * (x / static_cast<float>(width_-1)));
				for (int y = 0; y < height_; ++y) {
					for (int sx = 0, i = x + (height_ -1 - y) * width_; sx < 2; ++sx) {
						for (int sy = 0; sy < 2; ++sy, color = Vec3()) {
							for (int n = 0; n < samples; ++n) {
								double a = distribution(generator);
								double b = distribution(generator);
								a = a < 1 ? std::sqrt(a) - 1 : 1 - std::sqrt(2 - a);
								b = b < 1 ? std::sqrt(b) - 1 : 1 - std::sqrt(2 - b);
								Vec3 dir = ((((sx + 0.5 + a) / 2 + x) / width_ ) - 0.5) * cx  +
													 ((((sy + 0.5 + b) / 2 + y) / height_) - 0.5) * cy + cam.direction_;
								normalize(dir);
								color += Ray(cam.origin_+100*dir, dir).trace(spheres, 0) * (1.0 / samples);
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

		void save(const char *file) const {
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