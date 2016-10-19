/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-23 11:09:37
**/

#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include <memory>

#include "../core/object.hpp"

namespace Giraffe {

class Triangle : public Object
{
	public:
		Triangle(	const Point3d &a, const Point3d &b, const Point3d &c,
							const std::shared_ptr<Texture> &texture)
		:a_(a), b_(b), c_(c), texture_(texture) {
			normal_ = normalize(cross(c_-a_, b_-a_));
		}

		bool intersect(const Ray &, Isect &) const override;

		std::ostream& print(std::ostream &os) const override {
			return os << "triangle\n" << a_ << b_ << c_ << normal_;
		}

		bool emit() const override { return texture_->emit(); }

	private:
		Point3d  a_, b_, c_;
		Vector3d normal_;
		std::shared_ptr<Texture> texture_;
};

} // namespace Giraffe

#endif /* _TRIANGLE_HPP_ */