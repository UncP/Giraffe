/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:56:57
**/

#ifndef _NOISE_HPP_
#define _NOISE_HPP_

#include "../math/constant.hpp"
#include "../math/point.hpp"

namespace Giraffe {

#define CR00 -0.5
#define CR01  1.5
#define CR02 -1.5
#define CR03  0.5
#define CR10  1.0
#define CR11 -2.5
#define CR12  2.0
#define CR13 -0.5
#define CR20 -0.5
#define CR21  0.0
#define CR22  0.5
#define CR23  0.0
#define CR30  0.0
#define CR31  1.0
#define CR32  0.0
#define CR33  0.0

template<typename T>
T spline(double x, int nknots, T *knot)
{
	int nspans = nknots - 4;
	x *= (double)nspans;
	int span = std::floor(x);
	x -= span;
	if (span > nspans)
		span = nspans;
	knot += span;
	T c3 = knot[0]*CR00 + knot[1]*CR01 + knot[2]*CR02 + knot[3]*CR03;
	T c2 = knot[0]*CR10 + knot[1]*CR11 + knot[2]*CR12 + knot[3]*CR13;
	T c1 = knot[0]*CR20 + knot[1]*CR21 + knot[2]*CR22 + knot[3]*CR23;
	T c0 = knot[0]*CR30 + knot[1]*CR31 + knot[2]*CR32 + knot[3]*CR33;
	return ((c3 * x + c2) * x + c1) * x + c0;
}

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

class Noise
{
	public:
		static const Noise& getNoise();

		constexpr static int PerlinNumber = 256;
		constexpr static int Mask = PerlinNumber - 1;

		Noise();

		int index(int, int, int) const;

		double gnoise(const Point3d &) const;

		double snoise(const Point3d &) const;

		double turbulence(const Point3d &) const;

		double fractalSum(const Point3d &) const;

		double glattice(int, int, int, double, double, double) const;

	private:
		int     octaves_;
		int     permutationTable_[2 * PerlinNumber];
		double  gradientTable_[3 * PerlinNumber];
};

} // namespace Giraffe

#endif /* _NOISE_HPP_ */