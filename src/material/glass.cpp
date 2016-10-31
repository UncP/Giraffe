/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 22:59:36
**/

#include "glass.hpp"

namespace Giraffe {

Color Glass::sample(const Vector3d &out, Vector3d &in, const Vector3d &Normal, double &pdf)
{
	bool into = true;
	Vector3d normal = Normal;
	if (dot(out, normal) > 0) normal = -normal, into = false;
	double etai = 1.0, etat = 1.5;
	double ior;
	if (into) ior = 1.0 / 1.5;
	else 			ior = 1.5;

	double cos1 = -dot(out, normal), cos2;
	if ((cos2 = (1 - ior * ior * (1.0 - cos1 * cos1))) < 0.0) {
		pdf = 1;
		return color_;
	}

	Vector3d refr = normalize(out * ior + normal * (ior * cos1 - std::sqrt(cos2)));
	Point3d refrPos = reflPos - 2 * normal * kEpsilon;

	double a = etat - etai, b = etat + etai;
	double R0 = a * a / (b * b), c = 1 - (into ? cos1 : -dot(refr, normal));
	double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re;

	pdf = Re;
	return refl;
	// double P = 0.25 + 0.5 * Re, RP = Re / P, TP = Tr / (1 - P);
	// return emission + mult(color, (depth > 2 ? (Sampler::get1D() < P ?
	// 	trace(Ray(reflPos, refl), depth)*RP : trace(Ray(refrPos, refr), depth)*TP):
	// 	trace(Ray(reflPos, refl), depth)*Re + trace(Ray(refrPos, refr), depth)*Tr));
}

} // namespace Giraffe
