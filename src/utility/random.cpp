/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-07-30 14:30:29
**/

#include "random.hpp"

namespace Giraffe {

std::default_random_engine RandomNumberGenerator::generator(time(0));
std::uniform_real_distribution<double> RandomNumberGenerator::distribution1( 0, 1);
std::uniform_real_distribution<double> RandomNumberGenerator::distribution2(-1, 1);

} // namespace Giraffe
