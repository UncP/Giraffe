/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-08-04 19:29:25
**/

#include "sphere.hpp"

void Sphere::computeBox(std::vector<double> &near, std::vector<double> &far,
	const Vec *normal) const
{
	for (size_t i = 0, end = near.size(); i != end; ++i) {
		double p = dot(c_, normal[i]);
		double n = p - r_;
		double f = p + r_;
		if (n < near[i]) near[i] = n;
		if (f > far[i]) far[i] = f;
	}
}
