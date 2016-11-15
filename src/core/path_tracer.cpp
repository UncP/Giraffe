/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-06 18:24:38
**/

#include <vector>
#include <chrono>
#include <unistd.h>

#include "camera.hpp"
#include "path_tracer.hpp"
#include "sampler.hpp"
#include "material.hpp"
#include "../utility/isect.hpp"
#include "../utility/image_io.hpp"

namespace Giraffe {

GiraffePathTracer::GiraffePathTracer(const Scene *scene, int width, int height, int samples)
:scene_(scene), pixels_(new Vector3d[width * height]), width_(width), height_(height),
samples_(samples) { }

Vector3d GiraffePathTracer::trace(const Ray &ray, int depth)
{
	Isect isect;
	const std::vector<Object *> &objects = scene_->objects();
	size_t oend = objects.size();

	for (size_t i = 0; i != oend; ++i) objects[i]->intersect(ray, isect);

	if (isect.miss()) return Vector3d();

	double pdf;
	Vector3d refl_dir;
	Color color = isect.material()->brdf(isect, ray.direction(), refl_dir, pdf);

	if (++depth > 3) {
		double max = std::max(color.x_, std::max(color.y_, color.z_));
		if (scene_->sampler()->get1D() < max) color *= (1.0 / max);
		else return Vector3d();
	}

	Point3d pos = isect.position() + isect.normal() * kEpsilon;
	isect.setPosition(pos);

	Vector3d emission;
	if (isect.material()->type() & Material::kDiffuse) {
		const std::vector<Light *> &lights = scene_->lights();
		for (size_t i = 0, lend = lights.size(); i != lend; ++i) {
			bool flag = true;
			Vector3d light_dir = lights[i]->illuminate(isect);
			if (light_dir == Vector3d(0) || dot(light_dir, isect.normal()) < 0) continue;
			for (size_t j = 0; j != oend; ++j) {
				if (objects[j]->hit(Ray(pos, light_dir), isect.distance())) {
					flag = false;
					break;
				}
			}
			if (flag) {
				emission += mult(lights[i]->radiance(isect),
					isect.material()->evaluate(ray.direction(), light_dir, isect));
			}
		}
	}
	return emission + mult(color, trace(Ray(pos, refl_dir), depth));
}

void GiraffePathTracer::ray_tracing()
{
	double inv = 1.0 / samples_;
	const Camera &camera = scene_->camera();
	Sampler *sampler = scene_->sampler();

	auto beg = std::chrono::high_resolution_clock::now();
	// Vector3d color;
	#pragma omp parallel for schedule(dynamic) // private(color)
	for (int x = 0; x < width_; ++x) {
		fprintf(stderr,"\rprogress: %5.2f%%", 100 * (x / static_cast<float>(width_-1)));
		for (int y = 0; y < height_; ++y) {
			// for (int sx = 0, i = x + y * width_; sx < 2; ++sx) {
				// for (int sy = 0; sy < 2; ++sy, color = Vector3d()) {
					Vector3d color;
					for (int n = 0; n < samples_; ++n) {
						Point2d off = sampler->get2D();
						Point2d raster((x+off.x_)/width_, (y+off.y_)/height_);
						// Point2d raster((x+(sx+off.x_)*0.5)/width_, (y+(sy+off.y_)*0.5)/height_);
						Ray ray = camera.generateRay(raster);
						color += trace(ray, 0) * inv;
					}
					pixels_[x + y * width_] += color;
					// pixels_[i] += color * 0.25;
				// }
			// }
		}
	}

	auto end  = std::chrono::high_resolution_clock::now();
	auto Time = std::chrono::duration<double, std::ratio<1>>(end - beg).count();
	std::cerr << "\ntime: " << std::setw(8) << Time << "  s\n";

	save_png();
}

void GiraffePathTracer::save_ppm() const
{
	std::string file;
	ImageIO::save_ppm(width_, height_, pixels_, file);
}

void GiraffePathTracer::save_png() const
{
	std::string file;
	if (ImageIO::save_png(width_, height_, pixels_, file))
		execlp("subl", "subl", file.c_str(), NULL);
}

GiraffePathTracer::~GiraffePathTracer()
{
	if (pixels_)
		delete [] pixels_;
	if (scene_)
		delete scene_;
	pixels_ = nullptr;
	scene_  = nullptr;
}

} // namespace Giraffe
