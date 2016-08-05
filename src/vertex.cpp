/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-05 17:02:10
**/

#include "vertex.hpp"

std::ostream& operator<<(std::ostream &os, const Vertex &v) {
	return os << v.position_ << v.normal_;
}