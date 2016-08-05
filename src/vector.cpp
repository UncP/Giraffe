/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-08-01 15:36:10
**/

#include "vector.hpp"

template<> Vec Vec::Zero(0);

template<>
bool iVec::operator<(const iVec &v) const
{
	if (x_ == v.x_) {
		if (y_ == v.y_) {
			return z_ < v.z_;
		} else {
			return y_ < v.y_;
		}
	} else {
		return x_ < v.x_;
	}
}
