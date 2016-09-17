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
#include "../math/utility.hpp"

namespace Giraffe {

class Noise
{
	public:

		static const Noise& getNoise();

		constexpr static int PerlinNumber = 256;
		constexpr static int Mask = PerlinNumber - 1;

		Noise();

		int index(int, int, int) const;

		double gnoise(const Point3d &) const;

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