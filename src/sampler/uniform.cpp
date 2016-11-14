/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-07 10:54:16
**/

#include "uniform.hpp"

namespace Giraffe {

std::shared_ptr<Sampler> createUniformSampler(Slice &slice)
{
	assert(slice.eof());
	return std::shared_ptr<Sampler>(new UniformSampler());
}

} // namespace Giraffe
