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

#include <memory>

#include "object.hpp"
#include "../math/vertex.hpp"

namespace Giraffe {

class Sphere : public Object
{
	public:
		Sphere(	const Point3d &center, const double radis, const std::shared_ptr<Texture> &texture)
		:c_(center), r_(radis), r2_(radis * radis), inv2r_(1.0 / (2 * r_)), texture_(texture) { }

		void computeBox(std::vector<double> &near, std::vector<double> &far,
			const Vector3d *normal) const override;

		bool intersect(const Ray &r, Isect &isect) const override;

		std::ostream& print(std::ostream &os) const override { return os << "sphere\n" << c_; }

	private:
		Point3d 	c_;
		double 		r_;
		double 		r2_;
		double		inv2r_;
		std::shared_ptr<Texture> texture_;
};

} // namespace Giraffe

#endif /* _SPHERE_HPP_ */