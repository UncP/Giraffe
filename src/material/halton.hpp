/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-31 12:05:47
**/

#ifndef _HALTON_HPP_
#define _HALTON_HPP_

#include "../core/material.hpp"

namespace Giraffe {

class Halton : public Material
{
	public:
		Halton(Type type, const Vector3d &color)
		:Material(Type(type | kDiffuse)), color_(color) {
			assert(type == kHalton);
		}

		Color sample(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf)override;

	private:
		using Material::type_;
		Vector3d color_;
};

} // namespace Giraffe

#endif /* _HALTON_HPP_ */