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

#include "vector.hpp"

enum REFL { kDiffuse, kReflect, kRefract };

enum Plane { Xaxis = 0, Yaxis, Zaxis};

const uint8_t kNormalNumber = 7, kAABBNumber = 3, kDOPNumber = kNormalNumber;

const Vec NormalSet[kNormalNumber] = {
	Vec(1, 0, 0),
	Vec(0, 1, 0),
	Vec(0, 0, 1),
	Vec( std::sqrt(3)/3.0,  std::sqrt(3)/3.0, std::sqrt(3)/3.0),
	Vec(-std::sqrt(3)/3.0,  std::sqrt(3)/3.0, std::sqrt(3)/3.0),
	Vec(-std::sqrt(3)/3.0, -std::sqrt(3)/3.0, std::sqrt(3)/3.0),
	Vec( std::sqrt(3)/3.0, -std::sqrt(3)/3.0, std::sqrt(3)/3.0)
};

class Object;

class Isect
{
	public:
		Isect():dis_(kInfinity) { }

		inline void update(const double &d, const Object *o, const Vec &p, const Vec &n,
			const REFL &r, const Vec &c, const bool &emit, const Vec &e) {
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

		~Isect() { }

		double	dis_;
		const Object *object_;
		Vec 		position_;
		Vec 		normal_;
		REFL 		refl_;
		Vec 		color_;
		bool 		emit_;
		Vec 		emission_;
};

#endif /* _UITLITY_HPP_ */