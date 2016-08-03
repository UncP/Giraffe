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

const double PI 		= 3.141592653589793238;
const double DOU_PI = 2.0 * PI;
const double kInfinity  = std::numeric_limits<double>::max();
const double kRefractionRatio = 1.5;
const double kParallel = 1e-20;
const double kEpsilon = 1e-4;

enum REFL { kDiffuse, kReflect, kRefract };

enum Plane { Xaxis = 0, Yaxis = 1, Zaxis = 2 };

class Object;

class Isect
{
	public:
		Isect():dis_(kInfinity), obj_(nullptr) { }

		void update(const double &dis, const Object *obj) {
			if (dis > dis_ || dis < 0) return ;
			dis_ = dis;
			obj_ = const_cast<Object *>(obj);
		}

		bool miss() { return dis_ == kInfinity; }

		~Isect() { }

		double	dis_;
		Object *obj_;
};

#endif /* _UITLITY_HPP_ */