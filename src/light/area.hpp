/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-21 13:45:23
**/

#ifndef _AREA_LIGHT_HPP_
#define _AREA_LIGHT_HPP_

#include "../core/light.hpp"

namespace Giraffe {

class AreaLight : public Light
{
	public:
		AreaLight(const Point3d &position, const Vector3d &direction, const Vector3d &intensity,
			double angle);

		Vector3d sample(Isect &isect) const override;

		Vector3d radiance(const Isect &isect) const override;

	private:

		using Light::intensity_;

		Point3d  position_;
		Vector3d direction_;
		double   cos_max_;
};

} // namespace Giraffe

#endif /* _AREA_LIGHT_HPP_ */