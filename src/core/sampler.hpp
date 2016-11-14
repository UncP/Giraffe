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

#include <cassert>
#include <memory>

#include "../utility/slice.hpp"
#include "../math/point.hpp"
#include "../utility/random.hpp"

namespace Giraffe {

class Sampler
{
	public:
		Sampler() { }

		virtual double get1D() = 0;

		virtual Point2d get2D() = 0;

		virtual ~Sampler() { }

	protected:
		RandomNumberGenerator rng_;
};

Vector3d sampleCosHemisphere(const Vector3d &normal);

Vector3d sampleCosSphere(const Vector3d &normal, double sin_, double cos_);

} // namespace Giraffe

#endif /* _SAMPLER_HPP_ */