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

#include <cassert>

#include "../math/point.hpp"
#include "../math/vector.hpp"
#include "../utility/isect.hpp"

namespace Giraffe {

class Material
{
	public:
		enum Type { kDiffuse = 1,
								kReflect = 2,
								kRefract = 4,
								kGlossy  = 8,
								kHalton  = 16};

		Material(Type type):type_(type) { }

		Type type() const { return type_; }

		virtual Color sample(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf)
		= 0;

		virtual ~Material() { }

	protected:
		Type type_;
};

} // namespace Giraffe

#endif /* _MATERIAL_HPP_ */