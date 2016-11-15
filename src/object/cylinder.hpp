/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-20 22:58:36
**/

#ifndef _CYLINDER_HPP_
#define _CYLINDER_HPP_

#include "../math/point.hpp"
#include "../core/object.hpp"

namespace Giraffe {

class Cylinder : public Object
{
	public:
		Cylinder(	const Point3d &center1, const Point3d &center2, const double radis,
							const Material *material);

		bool intersect(const Ray &, Isect &) const override;

		void computeBox(std::vector<double> &, std::vector<double> &,
			const Vector3d *) const override;

		bool hit(const Ray &ray, const double &distance) const override;

		std::ostream& print(std::ostream &os) const override {
			return os << "cylinder\n" << center1_ << center2_ << radius_ << std::endl;
		}

	private:
		Point3d   center1_;
		Point3d   center2_;
		double    radius_;
		double    radius2_;
		double    inv2radius_;
		double    tmax_;
		Vector3d  axis_;
		const Material *material_;
};

} // namespace Giraffe

#endif /* _CYLINDER_HPP_ */