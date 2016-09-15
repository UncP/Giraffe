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

#include "../utility/random.hpp"
#include "../utility/utility.hpp"
#include "../object/object.hpp"
#include "../math/ray.hpp"

namespace Giraffe {

Vector3d trace(const Ray &, const std::vector<Object *> &, int);

} // namespace Giraffe

#endif /* _PATHTRACER_HPP_ */