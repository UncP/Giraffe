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
#include <ctime>
#include <random>

#include "sphere.hpp"

class Camera;

class Ray
{
	friend Camera;
	public:
		Ray() = default;
		Ray(const Vec3 &origin, const Vec3 &dir):origin_(origin), dir_(dir) { }

		Vec3 trace(const std::vector<Sphere *> &, int);

		~Ray() { }

	private:
		Vec3 		origin_;
		Vec3 		dir_;
		Sphere* intersect(const std::vector<Sphere *> &, double &);
};

#endif /* _RAY_H_ */