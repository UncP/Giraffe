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

#include "vector.hpp"
#include "utility.hpp"

class Object
{
	public:
		Object() = default;

		virtual void intersect(const Vec &, const Vec &, Isect &) const = 0;

		virtual void computeAABB(Vec &, Vec &) const {
			std::cerr << "virtual function called :(\n";
			exit(-1);
		}

		virtual const Vec& center() const {
			std::cerr << "virtual function called :(\n";
			exit(-1);
			// return Vec::Zero;
		}

		virtual const Vec& color() const {
			std::cerr << "virtual function called :(\n";
			exit(-1);
			// return Vec::Zero;
		}

		virtual bool emit() const {
			std::cerr << "virtual function called :(\n";
			exit(-1);
			// return false;
		}

		virtual const Vec& emission() const {
			std::cerr << "virtual function called :(\n";
			exit(-1);
			// return Vec::Zero;
		}

		virtual REFL refl() const {
			std::cerr << "virtual function called :(\n";
			exit(-1);
			// return kDiffuse;
		}

		virtual ~Object() { }
};

#endif /* _OBJECT_HPP_ */