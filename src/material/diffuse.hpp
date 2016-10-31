/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 22:53:49
**/

#ifndef _DIFFUSE_MATERIAL_HPP_
#define _DIFFUSE_MATERIAL_HPP_

#include "../core/material.hpp"

namespace Giraffe {

class Diffuse : public Material
{
	public:
		Diffuse(Type type, const Vector3d &color):Material(type), color_(color) {
			assert(type == kDiffuse);
		}

		Color sample(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf)override;

	private:
		using Material::type_;
		Color color_;
};

} // namespace Giraffe

#endif /* _DIFFUSE_MATERIAL_HPP_ */