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

#include "../utility/isect.hpp"
#include "camera.hpp"
#include "path_tracer.hpp"
#include "../utility/sampler.hpp"
#include "../utility/image_io.hpp"
#include "material.hpp"

namespace Giraffe {

GiraffePathTracer::GiraffePathTracer(const Scene *scene, int width, int height, int samples)
:scene_(scene), width_(width), height_(height), samples_(samples),
 pixels_(new Vector3d[width_ * height_]) { }

Vector3d GiraffePathTracer::trace(const Ray &ray, int depth)
{
	Isect isect;
	const std::vector<Object *> &objects = scene_->objects();
	size_t oend = objects.size();

	for (size_t i = 0; i != oend; ++i)
		scene_->objects()[i]->intersect(ray, isect);

	if (isect.miss()) return Vector3d();

	Vector3d dir;
	Color color = isect.material()->sample(ray.direction(), dir, isect);

	if (++depth > 3) {
		double max = std::max(color.x_, std::max(color.y_, color.z_));
		if (Sampler::get1D() < max) color *= (1.0 / max);
		else return Vector3d(0);
	}

	Vector3d emission(0);

	// bool into = true;
	// if (dot(ray.direction(), normal) > 0) normal = -normal, into = false;

	Vector3d normal = normalize(isect.normal());
	isect.setNormal(normal);

	Point3d pos = isect.position() + normal * kEpsilon;
	isect.setPosition(pos);

	const std::vector<Light *> &lights = scene_->lights();
	for (size_t i = 0, lend = lights.size(); i != lend; ++i) {
		bool flag = true;
		Vector3d light_dir = lights[i]->sample(isect);
		if (light_dir == Vector3d(0) || dot(light_dir, normal) < 0) continue;
		for (size_t j = 0; j != oend; ++j) {
			if (objects[j]->hit(Ray(pos, light_dir), isect.distance()) &&
					objects[j] != isect.object()) {
				flag = false;
				break;
			}
		}
		if (flag) {
			emission += dot(normal, light_dir) * mult(lights[i]->radiance(isect), color);
		}
	}
	return emission + mult(color, trace(Ray(pos, dir), depth));

	// Vector3d refl = normalize(ray.direction() - 2 * dot(ray.direction(), normal) * normal);

	// if (mat == kReflect)
	// 	return emission + mult(color, trace(Ray(reflPos, refl), depth));

	// double etai = 1.0, etat = kRefractionRatio;
	// double ior;
	// if (into) ior = 1.0 / kRefractionRatio;
	// else 			ior = kRefractionRatio;

	// double cos1 = -dot(ray.direction(), normal), cos2;
	// if ((cos2 = (1 - ior * ior * (1.0 - cos1 * cos1))) < 0.0)
	// 	return emission + mult(color, trace(Ray(reflPos, refl), depth));

	// Vector3d refr = normalize(ray.direction() * ior + normal * (ior * cos1 - std::sqrt(cos2)));
	// Point3d refrPos = reflPos - 2 * normal * kEpsilon;

	// double a = etat - etai, b = etat + etai;
	// double R0 = a * a / (b * b), c = 1 - (into ? cos1 : -dot(refr, normal));
	// double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re;

	// double P = 0.25 + 0.5 * Re, RP = Re / P, TP = Tr / (1 - P);
	// return emission + mult(color, (depth > 2 ? (Sampler::get1D() < P ?
	// 	trace(Ray(reflPos, refl), depth)*RP : trace(Ray(refrPos, refr), depth)*TP):
	// 	trace(Ray(reflPos, refl), depth)*Re + trace(Ray(refrPos, refr), depth)*Tr));
}

void GiraffePathTracer::ray_tracing()
{
	Vector3d color;
	double inv = 1.0 / samples_;
	auto beg = std::chrono::high_resolution_clock::now();
	const Camera &camera = scene_->camera();
	#pragma omp parallel for schedule(dynamic) private(color)
	for (int x = 0; x < width_; ++x) {
		fprintf(stderr,"\rprogress: %5.2f%%", 100 * (x / static_cast<float>(width_-1)));
		for (int y = 0; y < height_; ++y) {
			for (int sx = 0, i = x + y * width_; sx < 2; ++sx) {
				for (int sy = 0; sy < 2; ++sy, color = Vector3d()) {
					for (int n = 0; n < samples_; ++n) {
						Point2d off = Sampler::get2D1();
						Point2d raster((x+(off.x_+sx+0.5)*0.5)/width_, (y+(off.y_+sy+0.5)*0.5)/height_);
						Ray ray = camera.generateRay(raster);
						color += trace(ray, 0) * inv;
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
