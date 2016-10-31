/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-31 21:56:09
**/

#ifndef _RETRO_MATERIAL_HPP_
#define _RETRO_MATERIAL_HPP_

#include "../core/material.hpp"

namespace Giraffe {

class Retro : public Material
{
	public:
		Retro(Type type, const Vector3d &color):Material(type), color_(color) {
			assert(type == kRetro);
		}

		Color sample(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf) override
		{
			in = -out;
			return color_;
		}

	private:
		using Material::type_;
		Vector3d color_;
};

} // namespace Giraffe

#endif /* _RETRO_MATERIAL_HPP_ */