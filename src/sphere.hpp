/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-24 15:22:09
**/

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "vector.hpp"

enum REFL { kDiffuse, kReflect, kRefract };

const double BIAS = 1e-4;

class Sphere
{
	public:
		Sphere(	const Vec3 &center,
						const double radis,
						const Vec3 &color 	 = Vec3(0.0),
						const Vec3 &emission = Vec3(0.0),
						const REFL &refl 		 = kDiffuse)
		:	center_(center), radis_(radis), radis2_(radis * radis), refl_(refl), color_(color),
			emission_(emission) { }

		double intersect(const Vec3 &pos, const Vec3 &dir) const {
			Vec3 posToCenter = center_ - pos;
			double project = dot(posToCenter, dir);
			double det = radis2_ + project * project - posToCenter.length2();
			if (det < 0)
				return 0;
			else
				det = std::sqrt(det);
			double dis;
			return (dis = project - det) > BIAS ? dis : ((dis = project + det) > BIAS ? dis : 0);
		}

		~Sphere() { }

		Vec3 		center_;
		double 	radis_;
		double 	radis2_;
		REFL 		refl_;
		Vec3 		color_;
		Vec3		emission_;
};

#endif /* _SHAPE_H_ */