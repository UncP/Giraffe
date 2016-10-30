/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 22:38:35
**/

#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include "../math/point.hpp"
#include "../math/vector.hpp"
#include "../utility/isect.hpp"

namespace Giraffe {

class Material
{
	public:
		virtual Color sample(const Vector3d &out, Vector3d &in, const Isect &isect) = 0;

		virtual ~Material() { }
};

} // namespace Giraffe

#endif /* _MATERIAL_HPP_ */