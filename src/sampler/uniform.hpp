/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-07 10:52:05
**/

#ifndef _UNIFORM_SAMPLER_HPP_
#define _UNIFORM_SAMPLER_HPP_

#include "../core/sampler.hpp"

namespace Giraffe {

class UniformSampler : public Sampler
{
	public:
		double get1D() override {
			return rng_.Uniform1();
		}

		Point2d get2D() override {
			return Point2d(rng_.Uniform1(), rng_.Uniform1());
		}
};

std::shared_ptr<Sampler> createUniformSampler(Slice &slice);

} // namespace Giraffe

#endif /* _UNIFORM_SAMPLER_HPP_ */