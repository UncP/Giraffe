/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-06 18:24:38
**/

#include "../utility/random.hpp"
#include "../utility/utility.hpp"

#include "pathTracer.hpp"

namespace Giraffe {

Vector3d PathTracer::trace(
	const Ray &ray,
	const std::vector<Object *> &objects,
	const std::vector<Light *> &lights,
	int depth)
{
	Isect isect;
	for (size_t i = 0, end = objects.size(); i != end; ++i)
		objects[i]->intersect(ray, isect);

	if (isect.miss()) return Vector3d();

	Vector3d color(isect.color());
	Vector3d emission(isect.emission());

	double max = std::max(color.x_, std::max(color.y_, color.z_));
	if (++depth > 5) {
		if (Random() < max) color *= (1.0 / max);
		else return emission;
	}

	Vector3d normal = normalize(isect.normal());

	bool into = true;
	if (dot(ray.direction(), normal) > 0) normal = -normal, into = false;

	Point3d reflPos = isect.position() + normal * kEpsilon;
	REFL mat = isect.refl();

	if (mat == kDiffuse) {
		size_t lend = lights.size(), oend = objects.size();
		for (size_t i = 0; i != lend; ++i) {
			bool flag = true;
			Vector3d dir(lights[i]->computeLight(reflPos, normal));
			if (dot(dir, normal) < 0) continue;
			for (size_t j = 0; j != oend; ++j) {
				if (objects[j]->hit(Ray(reflPos, dir))) {
					flag = false;
					break;
				}
			}
			if (flag) {
				emission += lights[i]->illuminate(isect);
			}
		}

		Vector3d u, v, w(normal);
		if (std::fabs(w.x_) > 0.1)
			u = normalize(cross(Vector3d(0, 1, 0), w));
		else
			u = normalize(cross(Vector3d(1, 0, 0), w));
		v = normalize(cross(w, u));
		double a = Random(), b = Random(), sini = std::sqrt(a), cosi = DOU_PI * b;
		Vector3d dir((sini*std::cos(cosi)*u) + (sini*std::sin(cosi)*v) + (std::sqrt(1-a)*w));

		return emission + mult(color, trace(Ray(reflPos, normalize(dir)), objects, lights, depth));
		// Vector3d e;
		// for (size_t i = 0, end = objects.size(); i != end; ++i) {
		// 	if (!objects[i]->emit()) continue;
		// 	Vector3d su, sv, sw(objects[i]->center() - reflPos);
		// 	if (std::fabs(sw.x_) > 0.1)
		// 		su = normalize(cross(Vector3d(0, 1, 0), sw));
		// 	else
		// 		su = normalize(cross(Vector3d(1, 0, 0), sw));
		// 	sv = normalize(cross(sw, su));
		// 	double cos_a_max = std::sqrt(1.0 - objects[i]->radis2() / dot(sw, sw));
		// 	double eps1 = Random(), eps2 = Random();
		// 	double cos_a = 1 - eps1 + eps1 * cos_a_max;
		// 	double sin_a = std::sqrt(1 - cos_a * cos_a);
		// 	double phi = DOU_PI * eps2;
		// 	Vector3d d(normalize(su*std::cos(phi)*sin_a + sv*std::sin(phi)*sin_a + sw*cos_a));
		// 	Object *obj = nullptr;
		// 	for (size_t j = 0; j != end; ++j)
		// 		if (objects[j]->intersect(Ray(reflPos, d), isect))
		// 			obj = objects[j];
		// 	if (obj == objects[i]) {
		// 		double omega = DOU_PI * (1.0 - cos_a_max);
		// 		e += mult(color, isect.emission() * dot(d, normal) * omega) * PI_INV;
		// 	}
		// }
	}

	Vector3d refl = normalize(ray.direction() - 2 * dot(ray.direction(), normal) * normal);

	if (mat == kReflect)
		return emission + mult(color, trace(Ray(reflPos, refl), objects, lights, depth));

	double etai = 1.0, etat = kRefractionRatio;
	double ior;
	if (into) ior = 1.0 / kRefractionRatio;
	else 			ior = kRefractionRatio;

	double cos1 = -dot(ray.direction(), normal), cos2;
	if ((cos2 = (1 - ior * ior * (1.0 - cos1 * cos1))) < 0.0)
		return emission + mult(color, trace(Ray(reflPos, refl), objects, lights, depth));

	Vector3d refr = normalize(ray.direction() * ior + normal * (ior * cos1 - std::sqrt(cos2)));
	Point3d refrPos = isect.position() - normal * kEpsilon;

	double a = etat - etai, b = etat + etai;
	double R0 = a * a / (b * b), c = 1 - (into ? cos1 : -dot(refr, normal));
	double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re;

	double P = 0.25 + 0.5 * Re, RP = Re / P, TP = Tr / (1 - P);
	return emission + mult(color, (depth > 2 ? (Random() < P ?
		trace(Ray(reflPos, refl), objects, lights, depth)*RP:
		trace(Ray(refrPos, refr), objects, lights, depth)*TP):
		trace(Ray(reflPos, refl), objects, lights, depth)*Re+
		trace(Ray(refrPos, refr), objects, lights, depth)*Tr));
}

} // namespace Giraffe
