/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 23:00:05
**/

#ifndef _GLASS_MATERIAL_HPP_
#define _GLASS_MATERIAL_HPP_

#include "../core/material.hpp"
#include "../core/texture.hpp"

namespace Giraffe {

class Glass : public Material
{
	public:

	private:
		const Texture *texture_;
};

} // namespace Giraffe

#endif /* _GLASS_MATERIAL_HPP_ */