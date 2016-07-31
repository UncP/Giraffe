/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-07-30 20:35:59
**/

#ifndef _BVH_HPP_
#define _BVH_HPP_

#include "vector.hpp"

class BoundingBox
{
	public:
		BoundingBox(const Vec &lbn, const Vec &rtf):lbn_(lbn), rtf_(rtf) { }

		double intersect(const Vec &, const Vec &) const;

		const Vec& operator[](const int i) const {
			assert(i >= 0 && i < 2)
			if (!i) return lbn_;
			return rtf_;
		}

		~BoundingBox() { }
	private:
		Vec lbn_, rtf_;
};

typedef BoundingBox BBox;

#endif /* _BVH_HPP_ */