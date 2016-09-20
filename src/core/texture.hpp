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

#include "../math/constant.hpp"
#include "../math/point.hpp"
#include "../math/vector.hpp"
#include "../math/vertex.hpp"
#include "../math/utility.hpp"
#include "../utility/intersection_info.hpp"
#include "noise.hpp"

namespace Giraffe {

class Texture
{
	public:
		Texture():refl_(kDiffuse), emit_(false) { }

		Texture(REFL refl, bool emit):refl_(refl), emit_(emit) { }

		virtual Vector3d evaluate(IntersectionInfo &) const = 0;

		REFL refl() const { return refl_; }

		Vector3d color(IntersectionInfo &surface) const {
			return !emit_ ? evaluate(surface) : Vector3d();
		}

		Vector3d emission(IntersectionInfo &surface) const {
			return emit_ ? evaluate(surface) : Vector3d();
		}

		virtual ~Texture() { }

	protected:
		REFL      refl_;
		bool      emit_;
};

} // namespace Giraffe

#endif /* _TEXTURE_HPP_ */