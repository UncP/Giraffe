/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-03 20:25:31
**/

#include "ray.hpp"

const double DOUBLE_MAX = std::numeric_limits<double>::max();
const double PI = 3.141592653589793238;
const double kRefractionRatio = 1.5;

static std::default_random_engine generator(time(0));
static std::uniform_real_distribution<double> distribution(0, 1);

Sphere* Ray::intersect(const std::vector<Sphere *> &spheres, double &near)
{
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

Vec3 Ray::trace(const std::vector<Sphere *> &spheres, int depth)
{
	double near = DOUBLE_MAX;
	Sphere *sphere = intersect(spheres, near);
	if (!sphere) return Vec3();

	Vec3 color(sphere->color_);
	double max = std::max(color.x_, std::max(color.y_, color.z_));
	if (++depth > 5) {
		if (distribution(generator) < max) color *= (1.0 / max);
		else return sphere->emission_;
	}

	Vec3 pos = origin_ + dir_ * near;
	Vec3 normal = pos - sphere->center_;
	normalize(normal);
	Vec3 newNormal(normal);

	bool into = true;
	if (dot(dir_, normal) > 0) newNormal = -newNormal, into = false;

	REFL mat = sphere->refl_;
	if (mat == kDiffuse) {
		Vec3 u, v, w(newNormal);
		if (std::fabs(w.x_) > 0.1)
			u = cross(Vec3(0, 1, 0), w);
		else
			u = cross(Vec3(1, 0, 0), w);
		normalize(u);
		v = cross(w, u);
		normalize(v);
		double a = distribution(generator), b = distribution(generator);
		double sini = std::sqrt(a), cosi = 2 * PI * b;
		Vec3 dir((sini * std::cos(cosi) * u) + (sini * std::sin(cosi) * v) + (std::sqrt(1 - a) * w));
		normalize(dir);
		return sphere->emission_ + color * Ray(pos, dir).trace(spheres, depth);
	} else if (mat == kReflect) {
		Vec3 refl = dir_ - 2 * dot(dir_, normal) * normal;
		normalize(refl);
		return sphere->emission_ + color * Ray(pos, refl).trace(spheres, depth);
	}
	Vec3 refl(dir_ - 2 * dot(dir_, normal) * normal);
	normalize(refl);
	double etai = 1.0, etat = kRefractionRatio;
	double ior;
	if (into)
		ior = 1.0 / kRefractionRatio;
	else
		ior = kRefractionRatio;
	double cos1 = -dot(dir_, newNormal), cos2;
	if ((cos2 = (1 - ior * ior * (1.0 - cos1 * cos1))) < 0.0)
		return sphere->emission_ + color * Ray(pos, refl).trace(spheres, depth);
	Vec3 refr(dir_ * ior + newNormal * (ior * cos1 - std::sqrt(cos2)));
	normalize(refr);
	double a = etat - etai, b = etat + etai;
	double R0 = a * a / (b * b), c = 1 - (into ? cos1 : dot(refr, normal));
	double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re;
	double P = 0.25 + 0.5 * Re, RP = Re / P, TP = Tr / (1 - P);
	return sphere->emission_ + color * (depth > 2 ?
		(distribution(generator) < P ? Ray(pos, refl).trace(spheres, depth) * RP :
																	 Ray(pos, refr).trace(spheres, depth) * TP) :
		Ray(pos, refl).trace(spheres, depth) * Re + Ray(pos, refr).trace(spheres, depth) * Tr);
}
