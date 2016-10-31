/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-31 18:22:40
**/

#include "glossy.hpp"

namespace Giraffe {

Color Glossy::sample(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf)
{
	in = normalize(out - (2 * dot(out, normal)) * normal);

	return color_;
}

} // namespace Giraffe
