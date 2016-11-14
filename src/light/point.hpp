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
		PointLight(const Point3d &position, const Vector3d &intensity);

		Vector3d illuminate(Isect &isect) const override;

		Vector3d radiance(const Isect &isect) const override;

	private:

		using Light::intensity_;

		Point3d  position_;
};

std::shared_ptr<Light> createPointLight(Slice &slice);

} // namespace Giraffe

#endif /* _POINT_LIGHT_HPP_ */