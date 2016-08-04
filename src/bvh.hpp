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

class Box : public Object
{
	public:
		Box() = default;

		const size_t size() const { return near_.size(); }

		bool intersect(const Ray &, Isect &) const override;

		Plane getSplitPlane() const {
			double x = far_[0] - near_[0];
			double y = far_[1] - near_[1];
			double z = far_[2] - near_[2];
			return x >= y && x >= z ? Xaxis : y >= z ? Yaxis : Zaxis;
		}

		void print() const override {
			std::cout << "box\n";
			for (size_t i = 0; i != near_.size(); ++i)
				std::cout << setw(8) << near_[i] << " ";
			std::cout << std::endl;
			for (size_t i = 0; i != far_.size(); ++i)
				std::cout << setw(8) << far_[i] << " ";
			std::cout << std::endl;
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
			for (size_t i = 0; i != 3; ++i) {
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
			for (size_t i = 0; i < kNormalNumber; ++i) {
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

		void traverse();

		void split(Box *, std::vector<Object*> &, std::vector<Box *> &);

		~BVHNode() { }

	private:
		shared_ptr<Object>	obj_;
		shared_ptr<BVHNode> left_;
		shared_ptr<BVHNode> right_;
};

class BVH : public Object
{
	public:
		BVH():root_(shared_ptr<BVHNode>(new BVHNode())) { }

		bool intersect(const Ray &, Isect &) const override;

		void print() const override;

		void build(std::vector<Object *> &);

		~BVH() { }

	private:
		shared_ptr<BVHNode> root_;
};

#endif /* _BVH_HPP_ */