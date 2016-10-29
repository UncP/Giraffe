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

namespace Giraffe {

class Material
{
	public:
		enum Type { kDiffuse, kReflect, kRefract };

		Vector3d sample(const Vector3d direction, Vector3d &normal, ) const = 0;

		virtual ~Material() { }
};

} // namespace Giraffe

#endif /* _MATERIAL_HPP_ */