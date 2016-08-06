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

		bool intersect(const Ray &r, Isect &isect) const override;

		std::ostream& print(std::ostream &os) const override { return os << "sphere\n" << c_; }

		const Vec& color() const override { return color_; }

		bool emit() const override { return emit_; }

		const Vec& emission() const override { return emission_; }

		REFL refl() const override { return refl_; }

		void computeBox(std::vector<double> &, std::vector<double> &, const Vec *) const override;

		~Sphere() { }

	protected:
		Vec 		c_;
		double 	r_;
		double 	r2_;
		bool 		emit_;
		REFL 		refl_;
		Vec 		color_;
		Vec			emission_;
};

class DynamicSphere : public Sphere
{
	public:
		DynamicSphere(const Vec &center,
									const double radis,
									const Vec &shift,
									const Vec &color 	 	 = Vec(0.0),
									const Vec &emission  = Vec(0.0),
									const REFL &refl 		 = kDiffuse)
		:Sphere(center, radis, color, emission, refl), shift_(shift) { }

		bool intersect(const Ray &r, Isect &isect) const override;

	private:
		Vec shift_;
};

#endif /* _SHAPE_H_ */