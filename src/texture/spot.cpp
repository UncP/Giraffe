/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-10 22:43:20
**/

#include "spot.hpp"

namespace Giraffe {

Vector3d SpotTexture::evaluate(Vertex &vertex) const
{
	double x = vertex.uv().x_ / radius_;
	double y = vertex.uv().y_ / radius_;
	x -= std::floor(x);
	y -= std::floor(y);
	x = 2 * (x - 0.5) * radius_;
	y = 2 * (y - 0.5) * radius_;
	return mix(color1_, color2_, (x * x + y * y) > (radius_ * radius_));
}

} // namespace Giraffe
