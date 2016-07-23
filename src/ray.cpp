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

Vec3 Ray::trace(const std::vector<Light *> &light, const std::vector<Sphere *> &spheres,
	int depth)
{
	if (++depth > 3) return Vec3(0);

	double near = DOUBLE_MAX;
	Sphere *hitSphere = intersect(spheres, near);

	// 没有物体与光线相交
	if (!hitSphere) return Vec3(0);

	// 相交点
	Vec3 hitPos 	 = origin_ + dir_ * near;
	// 相交点的法向量
	Vec3 hitNormal = hitSphere->center() - hitPos;
	normalize(hitNormal);

	bool into = true;
	// 如果法向量与光线同向,法向量取反
	if (dot(dir_, hitNormal) > 0) hitNormal = -hitNormal, into = false;

	Vec3 color(0.0);
	REFL mat = hitSphere->refl();
	if (mat == kDiffuse) {
		Vec3 newHitPos = hitPos + hitNormal * bias;
		// 判断反射光线是否处在其阴影内
		for (size_t i = 0, lEnd = light.size(); i != lEnd; ++i) {
			bool flag = true;
			// 反射光线方向
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
	} else if (mat == kReflect) {
		Vec3 newHitPos = hitPos + hitNormal * bias;
		Vec3 lightDir	 = dir_ - 2 * dot(dir_, hitNormal) * hitNormal;
		normalize(lightDir);
		color += Ray(newHitPos, lightDir).trace(light, spheres, depth);
	} else if (mat == kPhong) {
		Vec3 newHitPos = hitPos + hitNormal * bias;
		// 判断反射光线是否处在其阴影内
		for (size_t i = 0, lEnd = light.size(); i != lEnd; ++i) {
			bool flag = true;
			// 反射光线方向
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
		Vec3 reflDir	 = dir_ - 2 * dot(dir_, hitNormal) * hitNormal;
		normalize(reflDir);
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
