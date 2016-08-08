/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-07-30 14:30:29
**/

#include "random.hpp"

static std::default_random_engine generator(time(0));
static std::uniform_real_distribution<double> distribution(0, 1);

static std::default_random_engine generator2(time(0));
static std::uniform_real_distribution<double> distribution2(-1, 1);

double Random() { return distribution(generator); }

double Random2() { return distribution2(generator2); }