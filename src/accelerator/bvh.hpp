/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-01 15:19:23
**/

#ifndef _BVH_HPP_
#define _BVH_HPP_

#include <vector>
#include <memory>

#include "../math/constant.hpp"
#include "../core/object.hpp"
#include "box.hpp"

namespace Giraffe {

class BVHNode
{
	public:
		BVHNode():obj_(nullptr), left_(nullptr), right_(nullptr)  { }

		bool intersect(const Ray &, Isect &) const;

		std::ostream& traverse(std::ostream &os) {
			if (obj_) obj_->print(os);
			else			return os;
			if (left_ ) left_-> traverse(os);
			if (right_) right_->traverse(os);
			return os;
		}

		void split(Box *, std::vector<std::pair<Object *, Box *>> &, const size_t, const size_t);

	private:
		Object*	                 obj_;
		std::shared_ptr<BVHNode> left_;
		std::shared_ptr<BVHNode> right_;
};

class BVH : public Object
{
	public:
		BVH():root_(std::shared_ptr<BVHNode>(new BVHNode())) { }

		bool intersect(const Ray &, Isect &) const override;

		std::ostream& print(std::ostream &os) const override { root_->traverse(os); return os; }

		void build(std::vector<Object *> &objects);

	private:
		std::shared_ptr<BVHNode> root_;
};

} // namespace Giraffe

#endif /* _BVH_HPP_ */