/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-19 01:44:58
**/

#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "../math/vertex.hpp"
#include "noise.hpp"

namespace Giraffe {

class Texture
{
	public:
		Texture() { }

		virtual Vector3d evaluate(Vertex &vertex) const = 0;

		virtual ~Texture() { }
};

} // namespace Giraffe

#endif /* _TEXTURE_HPP_ */