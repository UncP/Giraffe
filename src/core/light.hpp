/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-18 18:28:00
**/

#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "../math/point.hpp"
#include "../math/vector.hpp"
#include "../utility/isect.hpp"

namespace Giraffe {

class Light
{
	public:

		Light(const Vector3d &intensity):intensity_(intensity) { }

		virtual Vector3d sample(Isect &isect) const = 0;

		virtual Vector3d radiance(const Isect &isect) const = 0;

		virtual ~Light() { }

	protected:

		Vector3d intensity_;

};

} // namespace Giraffe

#endif /* _LIGHT_HPP_ */