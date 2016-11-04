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

Vector3d MarbleTexture::evaluate(const Point3d &position, const Point2d &uv,
	Vector3d &normal) const
{
	double t = Noise::getNoise().fractalSum(position * frequency_);
	double tt = 2 * std::fabs(std::sin(position.z_ * frequency_ + t));

	if (tt < 1)
		return mix(color2_, color3_, tt);
	else {
		tt -= 1;
		return mix(color1_, color2_, tt);
	}
	// static Vector3d color[13] = {Vector3d(0.25, 0.25, 0.35), Vector3d(0.25, 0.25, 0.35),
	// 														 Vector3d(0.1, 0.1, 0.3), Vector3d(0.1, 0.1, 0.3),
	// 														 Vector3d(0.1, 0.1, 0.3),
	// 														 Vector3d(0.25, 0.25, 0.35), Vector3d(0.25, 0.25, 0.35),
	// 														 Vector3d(0.05, 0.05, 0.26), Vector3d(0.05, 0.05, 0.26),
	// 														 Vector3d(0.03, 0.03, 0.20), Vector3d(0.03, 0.03, 0.20),
	// 														 Vector3d(0.25, 0.25, 0.35), Vector3d(0.03, 0.03, 0.20)
	// 													  };
	// double t = Noise::getNoise().fractalSum(surface.position() * frequency_);
	// return spline(clamp(2 * t + 0.75, 0, 1), 12, color);
}

} // namespace Giraffe
