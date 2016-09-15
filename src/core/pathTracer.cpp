/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-06 18:24:38
**/

#include "pathTracer.hpp"

namespace Giraffe {

Vector3d trace(const Ray &ray, const std::vector<Object *> &objects, int depth)
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
		Vector3d u, v, w(normal);
		if (std::fabs(w.x_) > 0.1)
			u = normalize(cross(Vector3d(0, 1, 0), w));
		else
			u = normalize(cross(Vector3d(1, 0, 0), w));
		v = normalize(cross(w, u));
		double a = Random(), b = Random(), sini = std::sqrt(a), cosi = DOU_PI * b;
		Vector3d dir((sini*std::cos(cosi)*u) + (sini*std::sin(cosi)*v) + (std::sqrt(1-a)*w));

		return emission + mult(color, trace(Ray(reflPos, normalize(dir)), objects, depth));
	}

	Vector3d refl = normalize(ray.direction() - 2 * dot(ray.direction(), normal) * normal);

	if (mat == kReflect)
		return emission + mult(color, trace(Ray(reflPos, refl), objects, depth));

	double etai = 1.0, etat = kRefractionRatio;
	double ior;
	if (into) ior = 1.0 / kRefractionRatio;
	else 			ior = kRefractionRatio;

	double cos1 = -dot(ray.direction(), normal), cos2;
	if ((cos2 = (1 - ior * ior * (1.0 - cos1 * cos1))) < 0.0)
		return emission + mult(color, trace(Ray(reflPos, refl), objects, depth));

	Vector3d refr = normalize(ray.direction() * ior + normal * (ior * cos1 - std::sqrt(cos2)));
	Point3d refrPos = isect.position() - normal * kEpsilon;

	double a = etat - etai, b = etat + etai;
	double R0 = a * a / (b * b), c = 1 - (into ? cos1 : -dot(refr, normal));
	double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re;

	double P = 0.25 + 0.5 * Re, RP = Re / P, TP = Tr / (1 - P);
	return emission + mult(color, (depth > 2 ? (Random() < P ?
		trace(Ray(reflPos, refl), objects, depth)*RP:trace(Ray(refrPos, refr), objects, depth)*TP):
		trace(Ray(reflPos, refl), objects, depth)*Re+trace(Ray(refrPos, refr), objects, depth)*Tr));
}

} // namespace Giraffe