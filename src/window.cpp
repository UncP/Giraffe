/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-07-30 17:18:13
**/

#include "window.hpp"

void Window::render(const Scene &scene, const int &samples)
{
	const Camera &camera = scene.camera();
	const std::vector<Sphere *> &spheres = scene.sphere();
	double inv = 1.0 / samples;
	Vec color;
	int max = (width_ - 1) + width_ * (height_ - 1);
	#pragma omp parallel for schedule(dynamic, 1) private(color)
	for (int x = 0; x < width_; ++x) {
		fprintf(stderr,"\rprogress: %5.2f%%", 100 * (x / static_cast<float>(width_-1)));
		for (int y = 0; y < height_; ++y) {
			for (int sx = 0, i = x + y * width_; sx < 2; ++sx) {
				for (int sy = 0; sy < 2; ++sy, color = Vec()) {
					for (int n = 0; n < samples; ++n) {
						double a = Random(), b = Random();
						Ray ray;
						camera.computeRay(x + (a + sx + 0.5) * 0.5, y + (b + sy + 0.5) * 0.5, ray);
						color += ray.trace(spheres, 0) * inv;
					}
					if (i > max) std::cout << "fuck" << std::endl;
					pixels_[i] += color * 0.25;
				}
			}
		}
	}
}
