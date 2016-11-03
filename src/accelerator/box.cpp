/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-03 12:54:57
**/

#include <algorithm>

#include "box.hpp"

namespace Giraffe {

static const Vector3d NormalSet[kNormalNumber] = {
	Vector3d(1, 0, 0),
	Vector3d(0, 1, 0),
	Vector3d(0, 0, 1),
	Vector3d( std::sqrt(3)/3.0,  std::sqrt(3)/3.0, std::sqrt(3)/3.0),
	Vector3d(-std::sqrt(3)/3.0,  std::sqrt(3)/3.0, std::sqrt(3)/3.0),
	Vector3d(-std::sqrt(3)/3.0, -std::sqrt(3)/3.0, std::sqrt(3)/3.0),
	Vector3d( std::sqrt(3)/3.0, -std::sqrt(3)/3.0, std::sqrt(3)/3.0)
};

Axis Box::getSplitPlane() const
{
	double x = far_[0] - near_[0];
	double y = far_[1] - near_[1];
	double z = far_[2] - near_[2];
	return x >= y && x >= z ? Xaxis : y >= z ? Yaxis : Zaxis;
}

void Box::enclose(const std::vector<std::pair<Object *, Box *>> &boxes, size_t beg, size_t end)
{
	for (size_t i = beg; i != end; ++i) {
		const Box *box = boxes[i].second;
		for (size_t j = 0; j != box->size(); ++j) {
			if (box->near_[j] < near_[j]) near_[j] = box->near_[j];
			if (box->far_[j] > far_[j]) 	far_[j] = box->far_[j];
		}
	}
}

void Box::enclose()
{
	std::for_each(objects_.begin(), objects_.end(), [this](const Object *object) {
		object->computeBox(near_, far_, NormalSet);
	});
}

bool Box::intersect(const Ray &ray, Isect &isect) const
{
	double tmin = -kInfinity, tmax = kInfinity;
	size_t size = near_.size();
	double no[size], nd[size];
	for (size_t i = 0; i != size; ++i) {
		no[i] = proj(ray.origin(), NormalSet[i]);
		nd[i] = 1.0 / dot(ray.direction(), NormalSet[i]);
	}
	for (size_t i = 0, end = near_.size(); i != end; ++i) {
		double min, max;
		// if ((std::fabs(nd[i]) < 1e-20) && ((no[i] - near_[i] < 0) || (far_[i] - no[i] < 0)))
			// return false;
		// nd[i] = 1.0 / nd[i];
		min = (near_[i] - no[i]) * nd[i];
		max = (far_[i]  - no[i]) * nd[i];
		if (nd[i] < 0) std::swap(min, max);
		if (max < 0) return false;
		if (min > tmin) tmin = min;
		if (max < tmax) tmax = max;
		if (tmin > tmax) return false;
	}
	return true;
}

} // namespace Giraffe
