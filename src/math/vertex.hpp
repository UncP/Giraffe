/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-05 16:58:49
**/

#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include "point.hpp"
#include "vector.hpp"

class Vertex
{
	public:

		Point3d 	position_;
		Vector3d 	normal_;

		Vertex() = default;

		Vertex(const Point3d &position, const Vector3d &normal)
		:position_(position), normal_(normal) { }
		Vertex& operator=(const Vertex &v) {
			position_ = v.position_;
			normal_ 	= v.normal_;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream &os, const Vertex &v) {
			return os << v.position_ << v.normal_;
		}
};

#endif /* _VERTEX_HPP_ */