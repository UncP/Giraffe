/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-07-30 14:29:28
**/

#ifndef _RANDOM_HPP_
#define _RANDOM_HPP_

#include <ctime>
#include <random>

namespace Giraffe {

class RandomNumberGenerator
{
	public:
		static double Uniform1() { return distribution1(generator); }
		static double Uniform2() { return distribution2(generator); }

	private:
		static std::default_random_engine generator;
		static std::uniform_real_distribution<double> distribution1;
		static std::uniform_real_distribution<double> distribution2;
};

} // namespace Giraffe

#endif /* _RANDOM_HPP_ */