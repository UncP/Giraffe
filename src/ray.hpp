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

#include "sphere.hpp"
#include "light.hpp"

const double DOUBLE_MAX = std::numeric_limits<double>::max();

class Ray
{
	public:
		Ray() = default;
		Ray(const Vec3 &origin, const Vec3 &dir = Vec3::Zero):origin_(origin), dir_(dir) { }

		Color trace(const std::vector<Sphere *> &, int, const std::vector<Light *> &);

		void computeDirection(const int width, const int height, const int x, const int y,
			const double ang) {
			dir_.x_ = (2 * ((x + 0.5) / width) - 1) * ang;
			dir_.y_ = (1 - 2 * ((y + 0.5) / height)) * ang;
			dir_.z_ = -1;
			normalize(dir_);
		}

		~Ray() { }

	private:
		Vec3 		origin_;
		Vec3 		dir_;
		Sphere* _findHitObject(const std::vector<Sphere *> &, double &);
};

#endif /* _RAY_H_ */