/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-01 16:25:28
**/

#ifndef _ISECT_HPP_
#define _ISECT_HPP_

#include "../math/constant.hpp"
#include "../math/point.hpp"
#include "../math/vector.hpp"

namespace Giraffe {

class Object;
class Material;

class Isect
{
	public:
		Isect():distance_(kInfinity) { }

		void update(const double &dis, const Object *object, const Point3d &position,
			const Vector3d &normal, const Point2d &uv, Material *material);

		void setDistance(const double &distance) { distance_ = distance; }
		void setPosition(const Point3d &position) { position_ = position; }
		void setNormal(const Vector3d &normal) { normal_ = normal; }

		bool  miss() const { return distance_ == kInfinity; }
		const double distance() const { return distance_; }
		const Object* object() const { return object_; }
		const Point3d& position() const { return position_; }
		const Vector3d& normal() const { return normal_; }
		Material* material() const { return material_; }

	private:

		double        distance_;
		const Object *object_;
		Point3d       position_;
		Vector3d      normal_;
		Point2d       uv_;
		Material     *material_;
};

} // namespace Giraffe

#endif /* _ISECT_HPP_ */