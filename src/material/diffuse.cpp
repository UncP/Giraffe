/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 22:57:25
**/

#include "../utility/sampler.hpp"
#include "diffuse.hpp"

namespace Giraffe {

Color Diffuse::sample(const Vector3d &out, Vector3d &in, const Isect &isect)
{
	Vector3d u, v, w(isect.normal());

	if (std::fabs(w.x_) > 0.1)
		u = normalize(cross(Vector3d(0, 1, 0), w));
	else
		u = normalize(cross(Vector3d(1, 0, 0), w));
	v = normalize(cross(w, u));
	double a = Sampler::get1D(), b = Sampler::get1D(), sini = std::sqrt(a), cosi = DOU_PI * b;

	in = normalize((sini*std::cos(cosi)*u) + (sini*std::sin(cosi)*v) + (std::sqrt(1-a)*w));

	return color_;
}

} // namespace Giraffe
