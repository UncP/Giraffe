/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-07-23 11:29:15
**/

#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <cmath>
#include <ctime>

#include "vector.hpp"

const double PI = 3.141592653589793238;

void reflect(const Vec3 &, const Vec3 &, Vec3 &);

void fresnel(const Vec3 &, const Vec3 &, const bool &, Vec3 &, double &);

#endif /* _UTILITY_HPP_ */