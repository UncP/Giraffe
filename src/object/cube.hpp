/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-15 11:21:15
**/

#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <memory>

#include "../math/ray.hpp"
#include "../utility/utility.hpp"

namespace Giraffe {

class Cube : public Object
{
	public:
		bool intersect(const Ray &, Isect &) const override;

		std::ostream& print(std::ostream &) const override;

	private:
		Point3d lbn_, rtf_;
		std::shared_ptr<Texture> texture_;
};

} // namespace Giraffe

#endif /* _CUBE_HPP_ */