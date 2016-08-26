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

#include <string>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <png.h>
#include <fstream>
#include <chrono>

#include "../math/ray.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "pathTracer.hpp"

class Window
{
	public:
		Window() = default;

		Window(const std::string &, const int, const int);

		void render(const Scene &, const int &);

		void show() const;
		void save_ppm() const;
		bool save_png() const;

		Window& operator=(const Window &) = delete;

		~Window() { delete [] pixels_; }

	private:
		std::string  title_;
		int 				 width_;
		int					 height_;
		Vector3d		*pixels_;
		uint32_t		*canvas_;
		SDL_Surface *screen_;
};

#endif /* _WINDOW_H_ */