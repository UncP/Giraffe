/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-07 11:06:36
**/

#include <cassert>

#include "stratified.hpp"

namespace Giraffe {

StratifiedSampler::StratifiedSampler(int xPixels, int yPixels):pixels_(xPixels * yPixels),
index1D_(0), index2D_(0)
{
	array1D_.reserve(pixels_);
	array2D_.reserve(pixels_);
	double invPixels = 1.0 / pixels_;
	for (int i = 0; i != pixels_; ++i)
		array1D_.push_back((rng_.Uniform1() + i) * invPixels);
	for (int i = 0; i != pixels_; ++i) {
		int other = i + rng_.Uniform1() * (pixels_-i);
		assert(other < pixels_);
		std::swap(array1D_[i], array1D_[other]);
	}
	double dx = 1.0 / xPixels;
	double dy = 1.0 / yPixels;
	for (int i = 0; i != xPixels; ++i) {
		for (int j = 0; j != yPixels; ++j) {
			Point2d p;
			p.x_ = (rng_.Uniform1() + i) * dx;
			p.y_ = (rng_.Uniform1() + j) * dy;
			array2D_.push_back(p);
		}
	}
	for (int i = 0; i != pixels_; ++i) {
		int other = i + rng_.Uniform1() * (pixels_-i);
		assert(other < pixels_);
		std::swap(array2D_[i], array2D_[other]);
	}
}

} // namespace Giraffe
