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

#include "vector.hpp"

class Vertex
{
	public:

		Vec 	position_;
		Vec 	normal_;

		Vertex() = default;

		Vertex(const Vec &position, const Vec &normal):position_(position), normal_(normal) { }
		Vertex& operator=(const Vertex &v) {
			position_ = v.position_;
			normal_ 	= v.normal_;
			return *this;
		}

		~Vertex() { }
};

typedef Vertex Vex;

std::ostream& operator<<(std::ostream &, const Vertex &);

#endif /* _VERTEX_HPP_ */