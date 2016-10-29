/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-08 17:43:50
**/

#ifndef _CONSTANT_HPP_
#define _CONSTANT_HPP_

#include <cmath>
#include <limits>

namespace Giraffe {

const double PI = 3.141592653589793238;
const double PI_INV = 1.0 / PI;
const double DOU_PI = 2.0 * PI;
const double DOU_PI_INV = 1.0 / DOU_PI;
const double kInfinity = std::numeric_limits<double>::max();
const double kRefractionRatio = 1.5;
const double kEpsilon = 1e-4;

enum REFL { kDiffuse, kReflect, kRefract };

enum Axis { Xaxis = 0, Yaxis, Zaxis};

inline double radian(double angle) {
	return angle * (PI / 180.0);
}

} // namespace Giraffe

#endif /* _CONSTANT_HPP_ */