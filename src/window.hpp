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

#include <SDL/SDL.h>
#include <vector>

#include "sphere.hpp"
#include "canvas.hpp"
#include "light.hpp"
#include "ray.hpp"

using std::vector;

class Window
{
	public:
		Window(const int width, const int height, const char *title)
			:width_(width), height_(height) {
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

			SDL_WM_SetCaption(title, NULL);

			canvas_ = new Canvas(static_cast<uint32_t *>(screen_->pixels), width_, height_);
			if (!canvas_) {
				std::cerr << "画布初始化失败 :(\n";
				exit(-1);
			}
		}

		void rayTrace(const Vec3 &origin, const double &fov, const vector<Light *> &light,
									const vector<Sphere *> &spheres) {
			double fac = tan(fov * PI / 360.0);
			Vec3 color;
#pragma omp parallel for private(color)
			for (int x = 0; x < width_; ++x) {
				for (int y = 0; y < height_; ++y, color=Vec3(0.0)) {
					Vec3 dir((2*((x+0.5)/width_)-1)*fac, (1-2*((y+0.5)/height_))*fac, -1);
					normalize(dir);
					color += Ray(origin, dir).trace(light, spheres, 0);
					canvas_->putPixel(x, y, color);
				}
			}
		}

		void show() const { SDL_UpdateRect(screen_, 0, 0, 0, 0); }

		void save(const char *file) const { canvas_->save(file); }

		Window(const Window &) = delete;
		Window& operator=(const Window &) = delete;

		~Window() { delete canvas_; }
	private:
		int 				 width_, height_;
		SDL_Surface *screen_;
		Canvas 			*canvas_;
};

#endif /* _WINDOW_H_ */