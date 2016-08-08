/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-06 18:24:38
**/

#include "pathTracer.hpp"

Vec trace(const Ray &ray, const std::vector<Object *> &objects, int depth)
{
	Isect isect;
	for (size_t i = 0, end = objects.size(); i != end; ++i)
		objects[i]->intersect(ray, isect);

	if (isect.miss()) return Vec::Zero;

	Vec &color 	= isect.color_;
	double max = std::max(color.x_, std::max(color.y_, color.z_));
	if (++depth > 5) {
		if (Random() < max) color *= (1.0 / max);
		else return isect.emission_;
	}

	Vec &pos 		= isect.position_;
	Vec &normal = isect.normal_;
	normalize(normal);

	bool into = true;
	if (dot(ray.dir_, normal) > 0) normal = -normal, into = false;

	Vec reflPos = pos + normal * kEpsilon;
	REFL mat = isect.refl_;

	if (mat == kDiffuse) {
		Vec u, v, w(normal);
		if (std::fabs(w.x_) > 0.1)
			u = cross(Vec(0, 1, 0), w);
		else
			u = cross(Vec(1, 0, 0), w);
		normalize(u);
		v = cross(w, u);
		normalize(v);
		double a = Random(), b = Random(), sini = std::sqrt(a), cosi = DOU_PI * b;
		Vec dir((sini*std::cos(cosi)*u) + (sini*std::sin(cosi)*v) + (std::sqrt(1-a)*w));
		normalize(dir);

		// Vec c;
		// for (int i = 0, end = objects.size(); i != end; ++i) {
		// 	if (!objects[i]->emit() || objects[i] == obj) continue;
		// 	Vec newDir(objects[i]->center() - obj->center());
		// 	normalize(newDir);
		// 	Object *obj;
		// 	if (!(obj = Ray(pos, newDir).intersect(objects, near)) || obj == objects[i])
		// 		c += objects[i]->emission() * color * std::max(0.0, dot(newDir, normal));
		// }

		return isect.emission_ + color * trace(Ray(reflPos, dir), objects, depth);
	}

	Vec refl = ray.dir_ - 2 * dot(ray.dir_, normal) * normal;
	normalize(refl);

	if (mat == kReflect)
		return isect.emission_ + color * trace(Ray(reflPos, refl), objects, depth);

	double etai = 1.0, etat = kRefractionRatio;
	double ior;
	if (into) ior = 1.0 / kRefractionRatio;
	else 			ior = kRefractionRatio;

	double cos1 = -dot(ray.dir_, normal), cos2;
	if ((cos2 = (1 - ior * ior * (1.0 - cos1 * cos1))) < 0.0)
		return isect.emission_ + color * trace(Ray(reflPos, refl), objects, depth);

	Vec refr(ray.dir_ * ior + normal * (ior * cos1 - std::sqrt(cos2)));
	Vec refrPos = pos - normal * kEpsilon;
	normalize(refr);

	double a = etat - etai, b = etat + etai;
	double R0 = a * a / (b * b), c = 1 - (into ? cos1 : -dot(refr, normal));
	double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re;

	double P = 0.25 + 0.5 * Re, RP = Re / P, TP = Tr / (1 - P);
	return isect.emission_ + color * (depth > 2 ? (Random() < P ?
		trace(Ray(reflPos, refl), objects, depth)*RP:trace(Ray(refrPos, refr), objects, depth)*TP):
		trace(Ray(reflPos, refl), objects, depth)*Re+trace(Ray(refrPos, refr), objects, depth)*Tr);
}
