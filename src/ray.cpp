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

Sphere* Ray::_findHitObject(const std::vector<Sphere *> &objects, double &near)
{	// 判断每个物体是否与光线相交
	// 若有相交, 找出与光线相交距离最短的那个物体
	Sphere *hitObject = nullptr;
	for (size_t i = 0, end = objects.size(); i != end; ++i) {
		double distance = objects[i]->intersect(origin_, dir_);
		if (distance > 0.0 && distance < near) {
			near = distance;
			hitObject = objects[i];
		}
	}
	return hitObject;
}

Color Ray::trace(const std::vector<Sphere *> &objects, int depth,
	const std::vector<Light *> &light)
{
	double near = DOUBLE_MAX;
	Sphere *hitObject = _findHitObject(objects, near);

	// 没有物体与光线相交
	if (!hitObject) return Color(0);

	// 相交点
	Vec3 hitPos 	 = origin_ + dir_ * near;
	// 相交点的法向量
	Vec3 hitNormal = hitObject->center() - hitPos;
	normalize(hitNormal);

	bool into = true;
	// 如果法向量与光线同向,法向量取反
	if (dot(dir_, hitNormal) > 0) hitNormal = -hitNormal, into = false;

	Color color(0.0);
	REFL mat = hitObject->refl();
	if (mat == DIFF) {
		Vec3 newHitPos = hitPos + hitNormal * bias;
		// 判断反射光线是否处在其阴影内
		for (size_t i = 0, end = light.size(); i != end; ++i) {
			bool flag = true;
			// 反射光线方向
			Vec3 lightDir;
			double intensity = light[i]->illuminate(hitPos, lightDir);
			for (size_t j = 0, oEnd = objects.size(); j != oEnd; ++j) {
				if (objects[j]->intersect(newHitPos, lightDir) > 0.0) {
					flag = false;
					break;
				}
			}
			if (flag)
				color += (intensity * std::max(0.0, dot(hitNormal, lightDir))) *
									hitObject->surfaceColor();
				// Vec3 h = lightDir - dir_;
				// normalize(h);
				// color += Color::White * pow(std::max(0.0, dot(hitNormal, h)), 32);
		}
	} else if (++depth < 3) {
		Vec3 reflDir = dir_ - 2 * dot(hitNormal, dir_) * hitNormal;
		normalize(reflDir);
		if (mat == SPEC) {
			color = Ray(hitPos, reflDir).trace(objects, depth, light);
		} else {	// REFR
			double cosi = -dot(dir_, hitNormal);
			double eta = into ? 1.0 / 1.1 : 1.1;
			double fresnelEffect = pow(1 - cosi, 3) * 0.9 + 0.1;
			double k = 1 - eta * eta * (1 - cosi * cosi);
			Vec3 refrDir = dir_ * eta + hitNormal * (eta * cosi - sqrt(k));
			normalize(refrDir);
			color = Ray(hitPos + hitNormal * bias, reflDir).trace(objects, depth, light) * fresnelEffect +
							Ray(hitPos - hitNormal * bias, refrDir).trace(objects, depth, light) *(1-fresnelEffect);
		}
	}
	return color;
}
