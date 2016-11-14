/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:42:56
**/

#include "constant.hpp"

namespace Giraffe {

std::shared_ptr<Texture> createConstantTexture(Slice &slice)
{
	Vector3d color = slice.findVector();
	assert(slice.eof());
	return std::shared_ptr<Texture>(new ConstantTexture(color));
}


} // namespace Giraffe
