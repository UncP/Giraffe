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

enum REFL { DIFF, SPEC, REFR };

class Sphere
{
	public:
		Sphere() = default;
		Sphere(	const Vec3 &center,
						const double radis,
						const Color &surfaceColor,
						const REFL refl = DIFF)
		:	center_(center), radis_(radis), radis2_(radis * radis),surfaceColor_(surfaceColor),
			refl_(refl) { }

		double intersect(const Vec3 &pos, const Vec3 &dir) const {
											// 光线起始点到球心的向量
			Vec3 posToCenter = center_ - pos;
											// 光线起始点到球心的向量在光线上的投影长度
			double projectLen = dot(posToCenter, dir);
											// 反向则不相交
			if (projectLen < 0) return -1.0;
											// 球心到光线的距离平方
			double distance2 = posToCenter.length2() - projectLen * projectLen;
											// 勾股定理判断球与光线是否有交点
			if (distance2 > radis2_) return -1.0;
			double distance = sqrt(radis2_ - distance2);
											// 更新光源到最近物体的距离
			return projectLen - distance;
		}

		const Vec3& center() const { return center_; }

		const Color surfaceColor() const {
			return surfaceColor_;
		}

		const REFL refl() const { return refl_; }

		~Sphere() { }

	private:
		Vec3 		center_;
		double 	radis_;
		double 	radis2_;
		Color 	surfaceColor_;
		REFL 		refl_;
};

#endif /* _SHAPE_H_ */