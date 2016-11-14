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
		StratifiedSampler(int xPixels, int yPixels);

		double get1D() override {
			return array1D_[index1D_++ % pixels_];
		}

		Point2d get2D() override {
			return array2D_[index2D_++ % pixels_];
		}

	private:
		int                  pixels_;
		std::atomic<int>     index1D_, index2D_;
		std::vector<double>  array1D_;
		std::vector<Point2d> array2D_;
};

std::shared_ptr<Sampler> createStratifiedSampler(Slice &slice);

} // namespace Giraffe

#endif /* _STRATIFIED_SAMPLER_HPP_ */