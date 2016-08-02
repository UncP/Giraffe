/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-01 15:19:23
**/

#ifndef _BVH_HPP_
#define _BVH_HPP_

#include <vector>
#include <memory>
#include <algorithm>

#include "object.hpp"

using std::shared_ptr;

// Axis-Aligned Bounding Box
class AABB : public Object
{
	public:
		AABB() = default;
		AABB(const Vec &lbn, const Vec &rtf):lbn_(lbn), rtf_(rtf) { }
		AABB(const AABB &box):lbn_(box.lbn_), rtf_(box.rtf_) { }

		AABB& operator=(const AABB &box) {
			lbn_ = box.lbn_;
			rtf_ = box.rtf_;
			return *this;
		}

		void intersect(const Vec &, const Vec &, Isect &) const override;

		const Vec& operator[](const int i) const {
			assert(i >= 0 && i < 2);
			if (!i) return lbn_;
			return rtf_;
		}

		Vec& operator[](const int i) {
			assert(i >= 0 && i < 2);
			if (!i) return lbn_;
			return rtf_;
		}

		Plane getSplitPlane() const {
			double x = rtf_.x_ - lbn_.x_, y = rtf_.y_ - lbn_.y_, z = lbn_.z_ - rtf_.z_;
			return x > y && x > z ? Xaxis : y > z ? Yaxis : Zaxis;
		}

		~AABB() { }

	private:
		Vec lbn_;		// left  bottom near
		Vec rtf_;		// right  top		far
};

class BVHNode
{
	public:
		BVHNode() { obj_ = nullptr; left_ = nullptr; right_ = nullptr; }

		bool intersect(const Vec &, const Vec &, Isect &) const;

		void split(const AABB &, std::vector<AABB> &);

		~BVHNode() { }
	private:
		shared_ptr<Object>	obj_;
		shared_ptr<BVHNode> left_;
		shared_ptr<BVHNode> right_;
};

class BVH : public Object
{
	public:
		BVH() { root_ = shared_ptr<BVHNode>(new BVHNode()); }

		void intersect(const Vec &, const Vec &, Isect &) const override;

		void build(const std::vector<Object *> &);

		~BVH() { }

	private:
		shared_ptr<BVHNode> root_;
};

#endif /* _BVH_HPP_ */