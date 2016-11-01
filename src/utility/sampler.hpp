/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-26 15:56:51
**/

#ifndef _SAMPLER_HPP_
#define _SAMPLER_HPP_

#include "../math/point.hpp"
#include "random.hpp"

namespace Giraffe {

class Sampler
{
	public:
		static double get1D() {
			return RandomNumberGenerator::Uniform1();
		}
		static Point2d get2D1() {
			return Point2d(RandomNumberGenerator::Uniform1(), RandomNumberGenerator::Uniform1());
		}
		static Point2d get2D2() {
			return Point2d(RandomNumberGenerator::Uniform2(), RandomNumberGenerator::Uniform2());
		}
};

Vector3d sampleCosHemisphere(const Vector3d &normal);
Vector3d sampleCosSphere(const Vector3d &normal, double sin_, double cos_);

} // namespace Giraffe

#endif /* _SAMPLER_HPP_ */