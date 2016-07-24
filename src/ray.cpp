/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-03 20:25:31
**/

#include "ray.hpp"

static const double bias = 1e-4;
static const int 		N = 16;
static const double pdf = 1.0 / (2 * PI);

std::default_random_engine generator(time(0));
std::uniform_real_distribution<double> distribution(0, 1);

Sphere* Ray::intersect(const std::vector<Sphere *> &spheres, double &near)
{	// 判断每个物体是否与光线相交
	// 若有相交, 找出与光线相交距离最短的那个物体
	Sphere *hitSphere = nullptr;
	for (size_t i = 0, end = spheres.size(); i != end; ++i) {
		double distance = spheres[i]->intersect(origin_, dir_);
		if (distance > 0.0 && distance < near) {
			near = distance;
			hitSphere = spheres[i];
		}
	}
	return hitSphere;
}

Vec3 Ray::trace(const std::vector<Light *> &light,
								const std::vector<Sphere *> &spheres,
								int depth)
{
	if (++depth > 3) return Vec3(0);

	double near = DOUBLE_MAX;
	Sphere *hitSphere = intersect(spheres, near);

	// 没有物体与光线相交
	if (!hitSphere) return Vec3(0);

	Vec3 hitPos 	 = origin_ + dir_ * near;
	Vec3 hitNormal = hitSphere->center() - hitPos;
	normalize(hitNormal);

	bool into = true;
	if (dot(dir_, hitNormal) > 0) hitNormal = -hitNormal, into = false;

	Vec3 color(0.0);
	REFL mat = hitSphere->refl();
	if (mat == kDiffuse) {
		Vec3 newHitPos = hitPos + hitNormal * bias;
		for (size_t i = 0, lEnd = light.size(); i != lEnd; ++i) {
			bool flag = true;
			Vec3 lightDir;
			double intensity = light[i]->illuminate(hitPos, lightDir);
			for (size_t j = 0, sEnd = spheres.size(); j != sEnd; ++j) {
				if (spheres[j]->intersect(newHitPos, lightDir) > 0.0) {
					flag = false;
					break;
				}
			}
			if (flag) color += (intensity * std::max(0.0, dot(hitNormal, lightDir))) *
													hitSphere->surfaceColor();
		}
		Vec3 giColor(0.0);
		Vec3 X, Y;
		createWorldCoordinate(hitNormal, X, Y);
		for (int i = 0; i < N; ++i) {
			double a = distribution(generator);
			double b = distribution(generator);
			Vec3 sample = uniformHemiSphere(a, b);
			Vec3 sampleDir(	sample.x_ * Y.x_ + sample.y_ * hitNormal.x_ + sample.z_ * X.x_,
											sample.x_ * Y.y_ + sample.y_ * hitNormal.y_ + sample.z_ * X.y_,
											sample.x_ * Y.z_ + sample.y_ * hitNormal.z_ + sample.z_ * X.z_);
			giColor += a * Ray(hitPos + sampleDir * bias, sampleDir).trace(light, spheres, depth);
		}
		giColor /= N;
		color = ((color / PI) + 2 * giColor);
	} else if (mat == kReflect) {
		Vec3 newHitPos = hitPos + hitNormal * bias;
		Vec3 reflDir;
		reflect(dir_, hitNormal, reflDir);
		color += Ray(newHitPos, reflDir).trace(light, spheres, depth);
	} else if (mat == kPhong) {
		Vec3 newHitPos = hitPos + hitNormal * bias;
		for (size_t i = 0, lEnd = light.size(); i != lEnd; ++i) {
			bool flag = true;
			Vec3 lightDir;
			double intensity = light[i]->illuminate(hitPos, lightDir);
			for (size_t j = 0, sEnd = spheres.size(); j != sEnd; ++j) {
				if (spheres[j]->intersect(newHitPos, lightDir) > 0.0) {
					flag = false;
					break;
				}
			}
			if (flag) {
				color += (intensity * std::max(0.0, dot(hitNormal, lightDir))) *
									hitSphere->surfaceColor();
				Vec3 h = lightDir - dir_;
				normalize(h);
				color += (intensity * std::pow(std::max(0.0, dot(h, hitNormal)), 32)) * Vec3::One;
			}
		}
	} else if (mat == kRefract) {
		Vec3 reflDir;
		reflect(dir_, hitNormal, reflDir);
		Vec3 refrDir;
		double kr = 0.0;
		fresnel(dir_, hitNormal, into, refrDir, kr);
		color += Ray(hitPos + hitNormal * bias, reflDir).trace(light, spheres, depth) * (1 - kr);
		if (kr != 0.0)
			color += Ray(hitPos - hitNormal * bias, refrDir).trace(light, spheres, depth) * kr;
		color *= hitSphere->surfaceColor();
	}
	return color;
}
