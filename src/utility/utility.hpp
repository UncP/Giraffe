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
#include "../math/vector.hpp"
#include "../math/point.hpp"
#include "../math/vertex.hpp"
#include "../core/texture.hpp"

namespace Giraffe {

class Isect
{
	public:
		Isect():dis_(kInfinity) { }

		inline void update(	const double &d, const Vertex &vertex, const Texture *t) {
			dis_ 		 = d;
			vertex_  = vertex;
			texture_ = t;
		}

		bool miss() const { return dis_ == kInfinity; }
		const double distance() { return dis_; }
		const Point3d& position() const { return vertex_.position(); }
		const Vector3d& normal() const { return vertex_.normal(); }
		Vector3d color() { return texture_->color(vertex_); }
		REFL refl() const { return texture_->refl(); }
		Vector3d emission() { return texture_->emission(vertex_); }

	private:
		double	       dis_;
		Vertex         vertex_;
		const Texture *texture_;
};

} // namespace Giraffe

#endif /* _UITLITY_UITLITY_HPP_ */