/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-07 11:06:25
**/

#ifndef _STRATIFIED_SAMPLER_HPP_
#define _STRATIFIED_SAMPLER_HPP_

#include <atomic>
#include <vector>

#include "../core/sampler.hpp"

namespace Giraffe {

class StratifiedSampler : public Sampler
{
	public:
		StratifiedSampler(int dimensions, int xPixels, int yPixels);

		void startNextSample() override {
			index1D_ = 0, index2D_ = 0;
			curr_dimension_ = 0;
		}

		double get1D() override {
			if (curr_dimension_ < dimensions_)
				return array1D_[curr_dimension_++][index1D_];
			else
				return rng_.Uniform1();
		}

		Point2d get2D() override {
			if (curr_dimension_ < dimensions_)
				return array2D_[curr_dimension_++][index2D_];
			else
				return Point2d(rng_.Uniform1(), rng_.Uniform1());
		}

	private:
		int                  pixels_;
		int                  dimensions_;
		std::atomic<int>     curr_dimension_;
		std::atomic<int>     index1D_, index2D_;
		std::vector<std::vector<double>>  array1D_;
		std::vector<std::vector<Point2d>> array2D_;
};

std::shared_ptr<Sampler> createStratifiedSampler(Slice &slice);

} // namespace Giraffe

#endif /* _STRATIFIED_SAMPLER_HPP_ */