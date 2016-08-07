/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-03 20:25:31
**/

#include "ray.hpp"

double Ray::Time = 0;

Ray::Ray(const Vec &ori, const Vec &dir):ori_(ori), dir_(dir) {
#ifdef AC
	for (size_t i = 0; i != kNormalNumber; ++i) {
		no_[i] = dot(ori_, NormalSet[i]);
		nd_[i] = 1.0 / dot(dir_, NormalSet[i]);
	}
#endif
}
