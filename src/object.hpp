/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-07-31 11:54:14
**/

#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <iostream>
#include <vector>

#include "vector.hpp"
#include "utility.hpp"
#include "ray.hpp"

class Object
{
	public:
		Object() = default;

		virtual bool intersect(const Ray &, Isect &) const = 0;

		virtual void computeBox(std::vector<double> &, std::vector<double> &,
			const Vec *) const {
			std::cerr << "virtual function called in Object :(\n";
			exit(-1);
		}

		virtual std::ostream& print(std::ostream &) const = 0;

		virtual ~Object() { }
};

std::ostream& operator<<(std::ostream &, const Object *);

#endif /* _OBJECT_HPP_ */