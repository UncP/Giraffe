/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:48:26
**/

#include "noise.hpp"

namespace Giraffe {

Vector3d NoiseTexture::evaluate(const Vertex &vertex) const
{
	double t = Noise::getNoise().gnoise(vertex.position() * frequency_);
	if (t < 0) t = 0;
	if (t > 1) t = 1;
	return mix(color1_, color2_, t);
}

} // namespace Giraffe
