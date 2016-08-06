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

const double PI = 3.141592653589793238;
const double DOU_PI = 2.0 * PI;
const double kInfinity = std::numeric_limits<double>::max();
const double kRefractionRatio = 1.5;
const double kEpsilon = 1e-4;

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
		Isect():dis_(kInfinity), obj_(nullptr) { }

		void update(const double &dis, const Object *obj, const Vec &normal) {
			dis_ 		= dis;
			obj_ 		= const_cast<Object *>(obj);
			normal_ = normal;
		}

		bool miss() { return dis_ == kInfinity; }

		~Isect() { }

		double	dis_;
		Object *obj_;
		Vec 		normal_;
};

#endif /* _UITLITY_HPP_ */