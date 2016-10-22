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
	size_t oend = objects.size();
#ifdef LIGHT
	oend -= 1;
#endif

	for (size_t i = 0; i != oend; ++i)
		objects[i]->intersect(ray, isect);

	if (isect.miss()) return Vector3d();

	Vector3d color(isect.color());
#ifdef LIGHT
	Vector3d emission(0);
	const Object *obj = isect.object();
#else
	Vector3d emission(isect.emission());
#endif
	double max = std::max(color.x_, std::max(color.y_, color.z_));
	if (++depth > 3) {
		if (Random() < max) color *= (1.0 / max);
		else return emission;
	}

	Vector3d normal = normalize(isect.normal());

	bool into = true;
	if (dot(ray.direction(), normal) > 0) normal = -normal, into = false;

	Point3d reflPos = isect.position() + normal * kEpsilon;
	isect.setPosition(reflPos);
	REFL mat = isect.refl();

	if (mat == kDiffuse) {

		#ifdef LIGHT
		size_t lend = lights.size();
		for (size_t i = 0; i != lend; ++i) {
			bool flag = true;
			Vector3d light(lights[i]->computeLight(isect));
			if (light == Vector3d(0) || dot(light, normal) < 0) continue;
			for (size_t j = 0; j != oend; ++j) {
				if (objects[j]->hit(Ray(reflPos, light), isect) && isect.object() != obj) {
					flag = false;
					break;
				}
			}
			if (flag) {
				emission += dot(normal, light) * mult(lights[i]->illuminate(isect), color);
			}
		}
		#endif

		Vector3d u, v, w(normal);
		if (std::fabs(w.x_) > 0.1)
			u = normalize(cross(Vector3d(0, 1, 0), w));
		else
			u = normalize(cross(Vector3d(1, 0, 0), w));
		v = normalize(cross(w, u));
		double a = Random(), b = Random(), sini = std::sqrt(a), cosi = DOU_PI * b;
		Vector3d dir((sini*std::cos(cosi)*u) + (sini*std::sin(cosi)*v) + (std::sqrt(1-a)*w));

		return emission + mult(color, trace(Ray(reflPos, normalize(dir)), objects, lights, depth));
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
	Point3d refrPos = reflPos - 2 * normal * kEpsilon;

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
