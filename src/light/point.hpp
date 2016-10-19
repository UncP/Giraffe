/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-18 18:30:52
**/

#ifndef _POINT_LIGHT_HPP_
#define _POINT_LIGHT_HPP_

#include "../core/light.hpp"

namespace Giraffe {

class PointLight : public Light
{
	public:
		PointLight(const Point3d &position, const Vector3d &intensity)
		:position_(position), intensity_(intensity) { }

		Vector3d illuminate(const Isect &isect) const override;

		Vector3d computeLight(const Point3d &position, const Vector3d &normal) const override;

	private:

		Point3d  position_;
		Vector3d intensity_;
};

} // namespace Giraffe

#endif /* _POINT_LIGHT_HPP_ */