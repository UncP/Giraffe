/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 22:57:34
**/

#ifndef _MIRROR_MATERIAL_HPP_
#define _MIRROR_MATERIAL_HPP_

#include "../core/material.hpp"

namespace Giraffe {

class Mirror : public Material
{
	public:
		Mirror(Type type):Material(type), color_(Vector3d(0.999)) {
			assert(type == kReflect);
		}

		Color sample(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf)override;

	private:
		using Material::type_;
		Vector3d color_;
};

} // namespace Giraffe

#endif /* _MIRROR_MATERIAL_HPP_ */