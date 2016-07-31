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
		Sphere(	const Vec &center,
						const double radis,
						const Vec &color 	 	 = Vec(0.0),
						const Vec &emission  = Vec(0.0),
						const REFL &refl 		 = kDiffuse)
		:	center_(center), radis_(radis), radis2_(radis * radis), refl_(refl), color_(color),
			emission_(emission) {
				if (emission_ == Vec(0.0)) emit_ = false;
				else 											 emit_ = true;
			}

		double intersect(const Vec &pos, const Vec &dir) const {
			Vec posToCenter = center_ - pos;
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

		Vec 		center_;
		double 	radis_;
		double 	radis2_;
		bool 		emit_;
		REFL 		refl_;
		Vec 		color_;
		Vec			emission_;
};

#endif /* _SHAPE_H_ */