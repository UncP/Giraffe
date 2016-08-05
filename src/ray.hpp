/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-03 20:16:46
**/

#ifndef _RAY_H_
#define _RAY_H_

#include <array>
#include <limits>

#include "utility.hpp"

class Ray
{
	public:
		Ray() = delete;

		Ray(const Vec &, const Vec &);

		~Ray() { }

		static double A;
		static double B;
		static void setDenominator(const double times) {
			B = times;
		}

		Vec ori_;
		Vec dir_;
		double fac_;
		std::array<double, kNormalNumber> no_;
		std::array<double, kNormalNumber> nd_;
};

#endif /* _RAY_H_ */