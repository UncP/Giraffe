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

#include <assert.h>
#include <memory>

#include "../math/point.hpp"
#include "object.hpp"

namespace Giraffe {

class Cylinder : public Object
{
	public:
		Cylinder(	const Point3d &center1, const Point3d &center2, const double radis,
							const std::shared_ptr<Texture> &texture);

		bool intersect(const Ray &, Isect &) const override;

		std::ostream& print(std::ostream &os) const override {
			return os << "cylinder\n" << center1_ << center2_ << radis_ << std::endl;
		}

	private:
		Point3d  center1_;
		Point3d  center2_;
		double   radis_;
		double   radis2_;
		double   inv2radis_;
		Vector3d axis_;
		std::shared_ptr<Texture> texture_;
};

} // namespace Giraffe

#endif /* _CYLINDER_HPP_ */