/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 17:02:47
**/

#ifndef _MATH_UTILITY_HPP_
#define _MATH_UTILITY_HPP_

namespace Giraffe {

inline double step(double a, double x)
{
	return x >= a;
}

template <typename T>
inline T mix(const T &a, const T &b, double t)
{
	return a * t + (1 - t) * b;
}

inline double clamp(double x, double a, double b)
{
	if (x < a) return a;
	if (x > b) return b;
	return x;
}

inline double smoothStep(double t)
{
	return t * t * (3 - 2 * t);
}

inline double lerp(double x, double y, double t)
{
	return t * x + (1 - t) * y;
}

} // namespace Giraffe

#endif /* _MATH_UTILITY_HPP_ */