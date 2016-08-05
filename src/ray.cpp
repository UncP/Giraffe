/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-03 20:25:31
**/

#include "ray.hpp"

double Ray::A = 0;
double Ray::B = 0;

Ray::Ray(const Vec &ori, const Vec &dir):ori_(ori), dir_(dir) {
	fac_ = ++A / B;
#ifdef AC
	for (size_t i = 0; i != kNormalNumber; ++i) {
		no_[i] = dot(ori_, NormalSet[i]);
		nd_[i] = 1.0 / dot(dir_, NormalSet[i]);
	}
#endif
}
