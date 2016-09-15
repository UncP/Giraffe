/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-01 16:25:28
**/

#ifndef _UITLITY_HPP_
#define _UITLITY_HPP_

#include "../math/constant.hpp"
#include "../math/vector.hpp"
#include "../math/point.hpp"
#include "../math/vertex.hpp"
#include "../core/texture.hpp"

namespace Giraffe {

class Isect
{
	public:
		Isect():dis_(kInfinity) { }

		inline void update(	const double &d, const Point3d &p, const Vector3d &n, const Point2d &uv,
												const Texture *t) {
			dis_ 			= d;
			position_ = p;
			normal_ 	= n;
			uv_				= uv;
			texture_  = t;
		}

		bool miss() const { return dis_ == kInfinity; }
		const double distance() { return dis_; }
		const Point3d& position() const { return position_; }
		const Vector3d& normal() const { return normal_; }
		Vector3d color() const { return texture_->color(Vertex(position_, normal_, uv_)); }
		REFL refl() const { return texture_->refl(); }
		Vector3d emission() const { return texture_->emission(Vertex(position_, normal_, uv_)); }

	private:
		double	       dis_;
		Point3d 		   position_;
		Point2d				 uv_;
		Vector3d 		   normal_;
		const Texture *texture_;
};

} // namespace Giraffe

#endif /* _UITLITY_HPP_ */