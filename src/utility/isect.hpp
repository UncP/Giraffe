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
#include "../math/vertex.hpp"

namespace Giraffe {

class Object;
class Material;

class Isect
{
	public:
		Isect():distance_(kInfinity) { }

		void update(const double &dis, const Object *object, const Point3d &position,
			const Vector3d &normal, const Point2d &uv, const Material *material);

		void setDistance(const double &distance) { distance_ = distance; }
		void setPosition(const Point3d &position) { vertex_.setPosition(position); }
		void setNormal(const Vector3d &normal) { vertex_.setNormal(normal); }

		bool  miss() const { return distance_ == kInfinity; }
		const double distance() const { return distance_; }
		const Object* object() const { return object_; }
		const Point3d& position() const { return vertex_.position(); }
		const Vector3d& normal() const { return vertex_.normal(); }
		Vertex& vertex() { return vertex_; }
		const Material* material() const { return material_; }

	private:

		double          distance_;
		const Object   *object_;
		Vertex          vertex_;
		// Point3d         position_;
		// Vector3d        normal_;
		// Point2d         uv_;
		const Material *material_;
};

} // namespace Giraffe

#endif /* _ISECT_HPP_ */