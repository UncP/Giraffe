/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 17:01:16
**/

#ifndef _PLANE_HPP_
#define _PLANE_HPP_

#include "../core/object.hpp"

namespace Giraffe {

class Plane : public Object
{
	public:

		Plane(const Point3d &position, const Vector3d &normal, const Texture *texture)
		:position_(position), normal_(normalize(normal)), texture_(texture) { }

		bool intersect(const Ray &, Isect &) const override;

		bool hit(const Ray &, Isect &) const override;

		std::ostream& print(std::ostream &os) const override {
			return os << "position: " << position_ << "normal: " << normal_;
		}

	private:
		Point3d  position_;
		Vector3d normal_;
		const Texture *texture_;
};

} // namespace Giraffe

#endif /* _PLANE_HPP_ */