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
		RandomNumberGenerator():generator_(time(0)), distribution1_(0, 1), distribution2_(-1, 1) { }

		double Uniform1() { return distribution1_(generator_); }

		double Uniform2() { return distribution2_(generator_); }

	private:
		std::default_random_engine generator_;
		std::uniform_real_distribution<double> distribution1_;
		std::uniform_real_distribution<double> distribution2_;
};

} // namespace Giraffe

#endif /* _RANDOM_HPP_ */