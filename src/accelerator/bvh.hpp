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
#include <map>
#include <algorithm>

#include "../object/object.hpp"

class Box : public Object
{
	public:
		Box() = default;

		const size_t size() const { return near_.size(); }

		bool intersect(const Ray &, Isect &) const override;

		void enclose(const std::vector<std::pair<Object *, Box *>> &boxes,
			const size_t beg, const size_t end) {
			for (size_t i = beg; i != end; ++i) {
				const Box *box = boxes[i].second;
				for (size_t j = 0, jEnd = box->size(); j != jEnd; ++j) {
					if (box->near_[j] < near_[j]) near_[j] = box->near_[j];
					if (box->far_[j] > far_[j]) 	far_[j] = box->far_[j];
				}
			}
		}

		Plane getSplitPlane() const {
			double x = far_[0] - near_[0];
			double y = far_[1] - near_[1];
			double z = far_[2] - near_[2];
			return x >= y && x >= z ? Xaxis : y >= z ? Yaxis : Zaxis;
		}

		std::ostream& print(std::ostream &os) const override {
			os << "box\n";
			for (size_t i = 0; i != near_.size(); ++i)
				os << std::setw(8) << near_[i] << " ";
			os << std::endl;
			for (size_t i = 0; i != far_.size(); ++i)
				os << std::setw(8) << far_[i] << " ";
			os << std::endl;
			return os;
		}

		~Box() { }

		std::vector<double> near_;
		std::vector<double> far_;
};

// Axis-Aligned Bounding Box
class AABB : public Box
{
	public:
		AABB() {
			for (size_t i = 0; i != kAABBNumber; ++i) {
				near_.push_back(kInfinity);
				far_.push_back(-kInfinity);
			}
		}
		~AABB() { }
};

// Discrete Oriented Polytopes
class DOP : public Box
{
	public:
		DOP() {
			for (size_t i = 0; i < kDOPNumber; ++i) {
				near_.push_back(kInfinity);
				far_.push_back(-kInfinity);
			}
		}
		~DOP() { }
};

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

		void release() {
			if (left_) left_->release();
			if (right_) right_->release();
			delete obj_;
		}

		~BVHNode() { }

	private:
		Object*									 obj_;
		std::shared_ptr<BVHNode> left_;
		std::shared_ptr<BVHNode> right_;
};

class BVH : public Object
{
	public:
		BVH():root_(std::shared_ptr<BVHNode>(new BVHNode())) { }

		bool intersect(const Ray &, Isect &) const override;

		std::ostream& print(std::ostream &os) const override { root_->traverse(os); return os; }

		void build(std::vector<Object *> &);

		~BVH() { root_->release(); }

	private:
		std::shared_ptr<BVHNode> root_;
};

#endif /* _BVH_HPP_ */