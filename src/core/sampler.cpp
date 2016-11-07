/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-26 18:00:52
**/

#include "../math/constant.hpp"
#include "sampler.hpp"
#include "../sampler/halton.hpp"

namespace Giraffe {

static RandomNumberGenerator rng;
// HaltonSampler halton(0, 2);

Vector3d sampleCosHemisphere(const Vector3d &normal)
{
	Vector3d u, v, w(normal);

	if (std::fabs(w.x_) > std::fabs(w.y_))
		u = normalize(cross(Vector3d(0, 1, 0), w));
	else
		u = normalize(cross(Vector3d(1, 0, 0), w));
	v = cross(w, u);

	double a = rng.Uniform1(), b = rng.Uniform1(), sini = std::sqrt(a), cosi = DOU_PI * b;
	// double a = halton.get1D(), b = halton.get1D(), sini = std::sqrt(1-a*a), cosi = DOU_PI * b;
	// return normalize(normal + Vector3d(std::cos(cosi)*sini, std::sin(cosi)*sini, std::sqrt(a)));
	return normalize((sini*std::cos(cosi)*u) + (sini*std::sin(cosi)*v) + (std::sqrt(1-a)*w));
}

Vector3d sampleCosSphere(const Vector3d &normal, double sin_, double cos_)
{
	Vector3d u, v, w(normal);

	if (std::fabs(w.x_) > 0.1)
		u = normalize(cross(Vector3d(0, 1, 0), w));
	else
		u = normalize(cross(Vector3d(1, 0, 0), w));
	v = normalize(cross(w, u));

	double a = rng.Uniform1(), phi = DOU_PI * a;

	return normalize((sin_*std::cos(phi)*u) + (sin_*std::sin(phi)*v) + (cos_*w));
}

} // namespace Giraffe
