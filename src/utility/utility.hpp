/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-01 16:25:28
**/

#ifndef _UITLITY_HPP_
#define _UITLITY_HPP_

#include "../math/math.hpp"
#include "../math/vector.hpp"
#include "../math/point.hpp"

enum REFL { kDiffuse, kReflect, kRefract };

enum Plane { Xaxis = 0, Yaxis, Zaxis};

const uint8_t kNormalNumber = 7, kAABBNumber = 3, kDOPNumber = kNormalNumber;

const Vector3d NormalSet[kNormalNumber] = {
	Vector3d(1, 0, 0),
	Vector3d(0, 1, 0),
	Vector3d(0, 0, 1),
	Vector3d( std::sqrt(3)/3.0,  std::sqrt(3)/3.0, std::sqrt(3)/3.0),
	Vector3d(-std::sqrt(3)/3.0,  std::sqrt(3)/3.0, std::sqrt(3)/3.0),
	Vector3d(-std::sqrt(3)/3.0, -std::sqrt(3)/3.0, std::sqrt(3)/3.0),
	Vector3d( std::sqrt(3)/3.0, -std::sqrt(3)/3.0, std::sqrt(3)/3.0)
};

class Object;

class Isect
{
	public:
		Isect():dis_(kInfinity) { }

		inline void update(const double &d, const Object *o, const Point3d &p, const Vector3d &n,
			const REFL &r, const Vector3d &c, const bool &emit, const Vector3d &e) {
			dis_ 			= d;
			object_ 	= o;
			position_ = p;
			normal_ 	= n;
			refl_ 		= r;
			color_ 		= c;
			emit_ 		= emit;
			emission_ = e;
		}

		bool miss() { return dis_ == kInfinity; }

		double	dis_;
		const Object *object_;
		Point3d 		position_;
		Vector3d 		normal_;
		REFL 				refl_;
		Vector3d 		color_;
		bool 				emit_;
		Vector3d 		emission_;
};

#endif /* _UITLITY_HPP_ */