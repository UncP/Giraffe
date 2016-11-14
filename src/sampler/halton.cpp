/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-07 11:12:43
**/

#include "halton.hpp"

namespace Giraffe {

std::shared_ptr<Sampler> createHaltonSampler(Slice &slice)
{
	int num1 = slice.findInteger();
	int num2 = slice.findInteger();
	assert(slice.eof());
	return std::shared_ptr<Sampler>(new HaltonSampler(num1, num2));
}


} // namespace Giraffe
