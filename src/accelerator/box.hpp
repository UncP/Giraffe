/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-03 12:52:29
**/

#ifndef _BOX_HPP_
#define _BOX_HPP_

#include "../core/object.hpp"

namespace Giraffe {


class Box : public Object
{
	public:
		Box() = default;

		static const int kNormalNumber = 7, kAABBNumber = 3, kDOPNumber = kNormalNumber;

		static Vector3d NormalSet[kNormalNumber];

		const size_t size() const { return near_.size(); }

		bool intersect(const Ray &ray, Isect &isect) const override;

		bool hit(const Ray &ray, const double &distance) const override;

		void enclose(const std::vector<std::pair<Object *, Box *>> &boxes, size_t beg, size_t end);

		void put(Object *object) {
			objects_.push_back(object);
		}

		void enclose();

		Axis getSplitPlane() const;

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

		double& near(size_t i) {
			assert(i < size());
			return near_[i];
		}

		double& far(size_t i) {
			assert(i < size());
			return far_[i];
		}

		std::vector<double>& near() { return near_; }

		std::vector<double>& far() { return far_; }

	protected:
		std::vector<double>   near_;
		std::vector<double>   far_;
		std::vector<Object *> objects_;

	private:
		bool intersect(const Ray &ray) const;

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
	private:
		using Box::near_;
		using Box::far_;
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
	private:
		using Box::near_;
		using Box::far_;
};

} // namespace Giraffe

#endif /* _BOX_HPP_ */