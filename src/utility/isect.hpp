/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-01 16:25:28
**/

#ifndef _UTILITY_UITLITY_HPP_
#define _UTILITY_UITLITY_HPP_

#include "../math/constant.hpp"
#include "intersection_info.hpp"
#include "../core/texture.hpp"

namespace Giraffe {

class Object;

class Isect
{
	public:
		Isect():dis_(kInfinity) { }

		void update(const double &d, const Object *object,
			const IntersectionInfo &surface, const Texture *t) {
			dis_ 		 = d;
			object_  = object;
			surface_ = surface;
			texture_ = t;
		}

		void update(const double &d, const Object *object) {
			dis_ 		 = d;
			object_  = object;
		}

		void setDistance(const double &dis) { dis_ = dis; }
		void setPosition(const Point3d &position) { surface_.setPosition(position); }

		bool miss() const { return dis_ == kInfinity; }
		const double distance() const { return dis_; }
		const Object* object() const { return object_; }
		const Point3d& position() const { return surface_.position(); }
		const Vector3d& normal() const { return surface_.normal(); }
		Vector3d evaluate() { return texture_->evaluate(surface_); }
		REFL refl() const { return texture_->refl(); }

	private:

		double           dis_;
		const Object    *object_;
		IntersectionInfo surface_;
		const Texture   *texture_;
};

} // namespace Giraffe

#endif /* _UITLITY_UITLITY_HPP_ */