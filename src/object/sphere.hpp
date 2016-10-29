/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-06-24 15:22:09
**/

#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include "../core/object.hpp"

namespace Giraffe {

class Sphere : public Object
{
	public:
		Sphere(const Point3d &center, const double radius, const Texture *texture)
		:center_(center), radius_(radius), radius2_(radius * radius),
		 inv2radius_(1.0 / (2 * radius_)), texture_(texture) { }

		void computeBox(std::vector<double> &near, std::vector<double> &far,
			const Vector3d *normal) const override;

		bool intersect(const Ray &r, Isect &isect) const override;

		bool hit(const Ray &r, Isect &) const override;

		std::ostream& print(std::ostream &os) const override {
			return os << "sphere\n" << center_ << "radius " << radius_ << std::endl;
		}

	private:
		Point3d 	     center_;
		double 		     radius_;
		double 		     radius2_;
		double		     inv2radius_;
		const Texture *texture_;
};

} // namespace Giraffe

#endif /* _SPHERE_HPP_ */