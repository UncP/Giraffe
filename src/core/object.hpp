/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-07-31 11:54:14
**/

#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <iostream>
#include <vector>

#include "../math/ray.hpp"
#include "../utility/utility.hpp"

namespace Giraffe {

class Object
{
	public:
		Object() = default;

		virtual bool intersect(const Ray &, Isect &) const = 0;

		virtual bool hit(const Ray &, Isect &) const { return false; }

		virtual void computeBox(std::vector<double> &, std::vector<double> &,
			const Vector3d *) const {
			std::cerr << "virtual function called in Object :(\n";
			exit(-1);
		}

		virtual std::ostream& print(std::ostream &) const = 0;

		friend std::ostream& operator<<(std::ostream &os, const Object *obj) {
			obj->print(os);
			return os;
		}

		virtual bool emit() const { return false; }

		virtual ~Object() { }
};

} // namespace Giraffe

#endif /* _OBJECT_HPP_ */