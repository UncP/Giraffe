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
static const int 		N 	 = 8;
static const double pdf  = 1.0 / (2 * PI);

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
	Vec3 hitNormal = hitPos - hitSphere->center();
	normalize(hitNormal);

	bool into = true;
	if (dot(dir_, hitNormal) > 0) hitNormal = -hitNormal, into = false;

	REFL mat = hitSphere->refl();
	if (mat == kDiffuse) {
		Vec3 color(0);
		Vec3 newHitPos = hitPos + hitNormal * bias;
		for (size_t i = 0, lEnd = light.size(); i != lEnd; ++i) {
			bool flag = true;
			Vec3 lightDir(hitNormal), intensity;
			double distance;
			light[i]->illuminate(hitPos, lightDir, intensity, distance);
			for (size_t j = 0, sEnd = spheres.size(); j != sEnd; ++j) {
				double dis = spheres[j]->intersect(newHitPos, lightDir);
				if (dis > 0.0 && dis < distance) {
					flag = false;
					break;
				}
			}
			if (flag)
				return hitSphere->albedo() * intensity * std::max(0.0, dot(hitNormal, lightDir));
		}
	} else if (mat == kReflect) {
		Vec3 newHitPos = hitPos + hitNormal * bias;
		Vec3 reflDir;
		reflect(dir_, hitNormal, reflDir);
		return Ray(newHitPos, reflDir).trace(light, spheres, depth);
	} else if (mat == kRefract) {
		Vec3 reflDir;
		reflect(dir_, hitNormal, reflDir);
		Vec3 refrDir;
		double kr = 0.0;
		fresnel(dir_, hitNormal, into, refrDir, kr);
		if (kr == 0.0)
			return Ray(hitPos + hitNormal * bias, reflDir).trace(light, spheres, depth) * (1 - kr) *
						 hitSphere->albedo();
		else
			return (Ray(hitPos + hitNormal * bias, reflDir).trace(light, spheres, depth) * (1 - kr) +
							Ray(hitPos - hitNormal * bias, refrDir).trace(light, spheres, depth) * kr) *
							hitSphere->albedo();
	}
	return Vec3(0);
}
