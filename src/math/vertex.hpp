/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-05 16:58:49
**/

#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include "point.hpp"
#include "vector.hpp"

namespace Giraffe {

class Vertex
{
	public:
		Vertex() = default;

		Vertex(const Point3d &position, const Vector3d &normal, const Point2d &uv)
		:position_(position), normal_(normal), uv_(uv) { }
		Vertex& operator=(const Vertex &v) {
			position_ = v.position_;
			normal_ 	= v.normal_;
			uv_       = v.uv_;
			return *this;
		}

		const Point3d& position() const { return position_; }
		const Vector3d& normal() const { return normal_; }
		const Point2d& uv() const { return uv_; }

	friend std::ostream& operator<<(std::ostream &os, const Vertex &v) {
		return os << v.position_ << v.normal_ << v.uv_;
	}

	private:
		Point3d 	position_;
		Vector3d 	normal_;
		Point2d   uv_;
};

} // namespace Giraffe

#endif /* _VERTEX_HPP_ */