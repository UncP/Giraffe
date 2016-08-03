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

#include "object.hpp"
#include "ray.hpp"

class Sphere : public Object
{
	public:
		Sphere(	const Vec &center,
						const double radis,
						const Vec &color 	 	 = Vec(0.0),
						const Vec &emission  = Vec(0.0),
						const REFL &refl 		 = kDiffuse)
		:c_(center), r_(radis), r2_(radis * radis), refl_(refl), color_(color), emission_(emission) {
			if (emission_ == Vec(0.0)) emit_ = false;
			else 											 emit_ = true;
		}

		bool intersect(const Ray &r, Isect &isect) const override {
			Vec l = c_ - r.ori_;
			double s = dot(l, r.dir_);
			double l2 = l.length2();
			if (s < 0 && l2 > r2_)
				return false;
			double q2 = l2 - s * s;
			if (q2 > r2_)
				return false;
			double q = std::sqrt(r2_ - q2);
			double dis = l2 > r2_ ? (s - q) : (s + q);
			isect.update(dis, this);
			return true;
			// Vec oriToCenter 	= pos_ - ori;
			// double projectLen = dot(posToCenter, dir);
			// double det = radis2_ + projectLen * projectLen - oriToCenter.length2();
			// if (det < 0)
			// 	return 0;
			// else
			// 	det = std::sqrt(det);
			// double dis;
			// return (dis = projectLen - det) > 0 ? dis : ((dis = projectLen + det) > 0 ? dis : 0);
		}

		void print() const override {
			std::cout << "sphere\n" << c_;
		}

		const Vec& center() const override { return c_; }

		const Vec& color() const override { return color_; }

		bool emit() const override { return emit_; }

		const Vec& emission() const override { return emission_; }

		REFL refl() const override { return refl_; }

		void computeAABB(Vec &lbn, Vec &rtf) const override {
			lbn = Vec(c_.x_-r_, c_.y_-r_, c_.z_-r_);
			rtf = Vec(c_.x_+r_, c_.y_+r_, c_.z_+r_);
		}

		~Sphere() { }

	private:
		Vec 		c_;
		double 	r_;
		double 	r2_;
		bool 		emit_;
		REFL 		refl_;
		Vec 		color_;
		Vec			emission_;
};

#endif /* _SHAPE_H_ */