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
#include "../core/texture.hpp"

namespace Giraffe {

class Mirror : public Material
{
	public:

	private:
		const Texture *texture_;
};

} // namespace Giraffe

#endif /* _MIRROR_MATERIAL_HPP_ */