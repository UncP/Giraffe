/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-03 20:25:31
**/

#include "ray.hpp"

Ray::Ray(const Vec3 &ori, const Vec3 &dir):ori_(ori), dir_(dir) {
	for (size_t i = 0; i != kNormalNumber; ++i) {
		no_[i] = dot(ori_, NormalSet[i]);
		nd_[i] = 1.0 / dot(dir_, NormalSet[i]);
	}
}
