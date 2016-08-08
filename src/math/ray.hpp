/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-03 20:16:46
**/

#ifndef _RAY_HPP_
#define _RAY_HPP_

#include "point.hpp"
#include "vector.hpp"

class Ray
{
	public:
		Ray(const Point3d &ori, const Vector3d &dir):ori_(ori), dir_(dir) { }

		~Ray() { }

		Point3d 	ori_;
		Vector3d 	dir_;
};

#endif /* _RAY_HPP_ */