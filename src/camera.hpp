/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-07-25 23:16:00
**/

#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "vector.hpp"

class Camera
{
	public:
		Camera(const Vec3 &origin, const Vec3 &direction):origin_(origin), direction_(direction) { }
		~Camera() { }

		Vec3 origin_;
		Vec3 direction_;
};

#endif /* _CAMERA_HPP_ */