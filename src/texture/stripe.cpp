/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:46:31
**/

#include "stripe.hpp"

namespace Giraffe {

Vector3d StripeTexture::evaluate(IntersectionInfo &surface) const
{
	Point3d p(transform_(surface.position()));
	double var = axis_ == Xaxis ? p.x_ : (axis_ == Yaxis ? p.y_ : p.z_);
	double t = (1.0 + std::sin((var * PI) * factor_)) * 0.5;
	return mix(color1_, color2_, t);
}

} // namespace Giraffe
