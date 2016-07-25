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

class Sphere
{
	public:
		Sphere(	const Vec3 &center,
						const double radis,
						const Vec3 &albedo = Vec3(0.18, 0.18, 0.18),
						const REFL &refl = kDiffuse)
		:	center_(center), radis_(radis), radis2_(radis * radis), refl_(refl), albedo_(albedo) { }

		double intersect(const Vec3 &pos, const Vec3 &dir) const {
			Vec3 posToCenter = center_ - pos;
			double project = dot(posToCenter, dir);
			double det = radis2_ + project * project - posToCenter.length2();
			if (det < 0)
				return 0;
			else
				det = std::sqrt(det);
			double bias = 1e-4;
			double dis;
			return (dis = project - det ) > bias ? dis : ((dis = project + det) > bias ? dis : 0);
		}

		const Vec3& center() const { return center_; }
		const Vec3& albedo() const { return albedo_; }
		const REFL& refl()	 const { return refl_; }
		~Sphere() { }

	private:
		Vec3 		center_;
		double 	radis_;
		double 	radis2_;
		REFL 		refl_;
		Vec3 		albedo_;
};

#endif /* _SHAPE_H_ */