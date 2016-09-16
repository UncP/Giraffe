/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-15 11:26:17
**/

#include "cube.hpp"

namespace Giraffe {

bool Cube::intersect(const Ray &ray, Isect &isect) const
{
	double near = -kInfinity, far = kInfinity;
	double no[3], nd[3];
	for (size_t i = 0; i != 3; ++i) {
		no[i] = ray.origin()[i];
		nd[i] = 1.0 / ray.direction()[i];
	}
	for (size_t i = 0; i != 3; ++i) {
		double min = (lbn_[i] - no[i]) * nd[i];
		double max = (rtf_[i] - no[i]) * nd[i];
		if (nd[i] < 0) std::swap(min, max);
		if (max < 0) return false;
		if (min > near) near = min;
		if (max < far) far = max;
		if (near > far) return false;
	}
	if (near < isect.distance()) {
		// isect.update(near, )
	}
	return true;
}

} // namespace Giraffe