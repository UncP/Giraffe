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
#include "../core/texture.hpp"

namespace Giraffe {

class Diffuse : public Material
{

	public:

	private:
		const Texture *texture_;
};

} // namespace Giraffe

#endif /* _DIFFUSE_MATERIAL_HPP_ */