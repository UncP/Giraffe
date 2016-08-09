/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-24 15:22:09
**/

#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include "object.hpp"

class Sphere : public Object
{
	public:
		Sphere(	const Point3d &center,
						const double 	radis,
						const Vector3d &color 	 = Vector3d(0),
						const Vector3d &emission = Vector3d(0),
						const REFL &refl 		 = kDiffuse)
		:c_(center), r_(radis), r2_(radis * radis), refl_(refl), color_(color), emission_(emission) {
			if (emission_ == Vector3d(0))
				emit_ = false;
			else
				emit_ = true;
		}

		void computeBox(std::vector<double> &near, std::vector<double> &far,
			const Vector3d *normal) const override
		{
			for (size_t i = 0, end = near.size(); i != end; ++i) {
				double p = proj(c_, normal[i]);
				double n = p - r_;
				double f = p + r_;
				if (n < near[i]) near[i] = n;
				if (f > far[i]) far[i] = f;
			}
		}

		bool intersect(const Ray &r, Isect &isect) const override {
			Vector3d l = c_ - r.ori_;
			double s = dot(l, r.dir_);
			double l2 = l.length2();
			if (s < 0 && l2 > r2_)
				return false;
			double q2 = l2 - s * s;
			if (q2 > r2_)
				return false;
			double q = std::sqrt(r2_ - q2);
			double dis = l2 > r2_ ? (s - q) : (s + q);

			if (dis < isect.dis_) {
				Point3d hitPos(r.ori_ + r.dir_ * dis);
				isect.update(dis, this, hitPos, hitPos - c_, refl_, color_, emit_, emission_);
			}
			return true;
		}

		std::ostream& print(std::ostream &os) const override { return os << "sphere\n" << c_; }

	private:
		Point3d 	c_;
		double 		r_;
		double 		r2_;
		bool 			emit_;
		REFL 			refl_;
		Vector3d 	color_;
		Vector3d	emission_;
};

#endif /* _SPHERE_HPP_ */