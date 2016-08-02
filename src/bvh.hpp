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
		AABB(const Vec &lbf, const Vec &rtn):lbf_(lbf), rtn_(rtn) { }
		AABB(const AABB &box):lbf_(box.lbf_), rtn_(box.rtn_) { }

		AABB& operator=(const AABB &box) {
			lbf_ = box.lbf_;
			rtn_ = box.rtn_;
			return *this;
		}

		void intersect(const Ray &, Isect &) const override;

		const Vec& operator[](const int i) const {
			assert(i >= 0 && i < 2);
			if (!i) return lbf_;
			return rtn_;
		}

		Vec& operator[](const int i) {
			assert(i >= 0 && i < 2);
			if (!i) return lbf_;
			return rtn_;
		}

		Plane getSplitPlane() const {
			double x = rtn_.x_ - lbf_.x_, y = rtn_.y_ - lbf_.y_, z = rtn_.z_ - lbf_.z_;
			return x > y && x > z ? Xaxis : y > z ? Yaxis : Zaxis;
		}

		~AABB() { }

	private:
		Vec lbf_;		// left  bottom far
		Vec rtn_;		// right  top		near
};

class BVHNode
{
	public:
		BVHNode() { obj_ = nullptr; left_ = nullptr; right_ = nullptr; }

		bool intersect(const Ray &, Isect &) const;

		void split(const AABB &, std::vector<Object*> &, std::vector<AABB> &);

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

		void intersect(const Ray &, Isect &) const override;

		void build(std::vector<Object *> &);

		~BVH() { }

	private:
		shared_ptr<BVHNode> root_;
};

#endif /* _BVH_HPP_ */