/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:49:51
**/

#include "marble.hpp"

namespace Giraffe {

Vector3d MarbleTexture::evaluate(Vertex &v) const
{
	double t = Noise::getNoise().fractalSum(v.position() * frequency_);
	double tt = 2 * std::fabs(std::sin(v.position().z_ * frequency_ + t));

	if (tt < 1)
		return color2_ * tt + (1 - tt) * color3_;
	tt -= 1;
	return color1_ * tt + (1 - tt) * color2_;
}

} // namespace Giraffe
