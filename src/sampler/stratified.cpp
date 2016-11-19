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

StratifiedSampler::StratifiedSampler(int dimension, int xPixels, int yPixels)
:pixels_(xPixels * yPixels), dimensions_(dimensions), curr_dimension_(0), index1D_(0),index2D_(0)
{
	for (int i = 0; i != dimensions_; ++i) {
		array1D_.push_back(std::vector<double>(pixels_));
		array2D_.push_back(std::vector<Point2d>(pixels_));
	}
	double invPixels = 1.0 / pixels_;
	for (int i = 0; i != dimensions_; ++i)
		for (int j = 0; j != pixels_; ++j)
			array1D_[i][j] = (rng_.Uniform1() + i) * invPixels;
	for (int i = 0; i != dimensions_; ++i)
		for (int j = 0; j != pixels_; ++j) {
			int other = j + rng_.Uniform1() * (pixels_-j);
			std::swap(array1D_[i][j], array1D_[i][other]);
		}
	double dx = 1.0 / xPixels;
	double dy = 1.0 / yPixels;
	for (int i = 0; i != dimensions_; ++i)
		for (int j = 0; j != xPixels; ++j) {
			for (int k = 0; k != yPixels; ++k) {
				Point2d p;
				p.x_ = (rng_.Uniform1() + j) * dx;
				p.y_ = (rng_.Uniform1() + k) * dy;
				array2D_[j][k] = p;
			}
		}
	for (int i = 0; i != dimensions_; ++i)
		for (int j = 0; j != pixels_; ++j) {
			int other = j + rng_.Uniform1() * (pixels_-j);
			std::swap(array2D_[i][j], array2D_[i][other]);
		}
}

std::shared_ptr<Sampler> createStratifiedSampler(Slice &slice)
{
	assert(slice.eof());
	return std::shared_ptr<Sampler>(new StratifiedSampler(1, 512, 512));
}

} // namespace Giraffe
