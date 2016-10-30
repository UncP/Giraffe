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
							Material *material);

		bool intersect(const Ray &, Isect &) const override;

		std::ostream& print(std::ostream &os) const override {
			return os << "cylinder\n" << center1_ << center2_ << radis_ << std::endl;
		}

	private:
		Point3d   center1_;
		Point3d   center2_;
		double    radis_;
		double    radis2_;
		double    inv2radis_;
		double    tmax_;
		Vector3d  axis_;
		Material *material_;
};

} // namespace Giraffe

#endif /* _CYLINDER_HPP_ */