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
#include "../utility/utility.hpp"

namespace Giraffe {

class Light
{
	public:
		virtual Vector3d illuminate(const Isect &isect) const = 0;

		virtual Vector3d computeLight(const Point3d &position, const Vector3d &normal) const = 0;

		~Light() { }

	private:

};

} // namespace Giraffe

#endif /* _LIGHT_HPP_ */