/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-03 20:16:46
**/

#ifndef _RAY_H_
#define _RAY_H_

#include <vector>
#include <limits>

#include "random.hpp"

class Ray
{
	public:
		Ray() = delete;

		Ray(const Vec3 &ori, const Vec3 &dir):ori_(ori), dir_(dir) {
			inv_ = Vec(1.0 / dir_.x_, 1.0 / dir_.y_, 1.0 / dir_.z_);
		}

		~Ray() { }

		Vec ori_;
		Vec dir_;
		Vec inv_;
};

#endif /* _RAY_H_ */