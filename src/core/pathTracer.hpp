/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-06 18:24:52
**/

#ifndef _PATHTRACER_HPP_
#define _PATHTRACER_HPP_

#include "../math/ray.hpp"
#include "object.hpp"
#include "light.hpp"

namespace Giraffe {

class PathTracer
{
	public:
		static Vector3d trace(const Ray &ray,
													const std::vector<Object *> &objects,
													const std::vector<Light *> &lights,
													int depth);
};

} // namespace Giraffe

#endif /* _PATHTRACER_HPP_ */