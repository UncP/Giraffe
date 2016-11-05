/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-05 22:33:53
**/

#ifndef _CONE_HPP_
#define _CONE_HPP_

#include "../core/object.hpp"

namespace Giraffe {

class Cone : public Object
{
	public:
		Cone(const Point3d &center, const Point3d &top, double radius, const Material *material)
		:center_(center), top_(top), raidus_(radius), material_(material) {
			assert(top_ != center_);
			axis_ = normalize(top_ - center_);
		}

		bool intersect(const Ray &, Isect &) const override;

		std::ostream& print(std::ostream &os) const override {
			return os << "cone\n" << center_ << top_ << "radius: " << radius_ << std::endl;
		}

	private:
		Point3d         center_;
		Point3d         top_;
		Vector3d        axis_;
		double          radius_;
		const Material *material_;
};

} // namespace Giraffe

#endif /* _CONE_HPP_ */