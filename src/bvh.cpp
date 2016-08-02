/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-01 15:21:29
**/

#include "bvh.hpp"

static bool _intersect(const double &o, const double &d, const double &s, const double &b,
	double &tmin, double &tmax)
{
	double parallel = std::fabs(d);
	if (parallel < kParallel) {
		if (o < s || o > b) return false;
	} else {
		double min, max, fac = 1.0 / d;
		min = (s - o) * fac;
		max = (b - o) * fac;
		if (min > max) std::swap(min, max);
		if (max < 0) return false;
		if (min > tmin) tmin = min;
		if (max < tmax) tmax = max;
		if (tmin > tmax) return false;
	}
	return true;
}

void AABB::intersect(const Vec &o, const Vec &d, Isect &isect) const
{
	double tmin = -kInfinity, tmax = kInfinity;
	if (!_intersect(o.x_, d.x_, lbn_.x_, rtf_.x_, tmin, tmax))
		return ;
	if (!_intersect(o.y_, d.y_, lbn_.y_, rtf_.y_, tmin, tmax))
		return ;
	if (!_intersect(o.z_, d.z_, lbn_.z_, rtf_.z_, tmin, tmax))
		return ;

	isect.update(tmin, this);
}

bool BVHNode::intersect(const Vec &o, const Vec &d, Isect &isect) const
{
	obj_->intersect(o, d, isect);
	if (isect.miss()) return false;

	if (!left_) return true;

	if (left_-> intersect(o, d, isect)) return true;
	if (right_->intersect(o, d, isect)) return true;
	return false;
}

void BVH::intersect(const Vec &o, const Vec &d, Isect &isect) const
{
	root_->intersect(o, d, isect);
}

static inline void _sortByPlane(std::vector<AABB> &box, const Plane &p)
{
	std::sort(box.begin(), box.end(),
		[p](const AABB &m, const AABB &n) { return m[1][p] < n[1][p]; });
}

static int _splitByPlane(const std::vector<AABB> &bounds)
{

}

void BVHNode::split(const AABB &box, std::vector<AABB> &bounds)
{
	obj_ = shared_ptr<Object>(new AABB(box));
	_sortByPlane(bounds, box.getSplitPlane());
	int pos = _splitByPlane(bounds);
}

static AABB _calculateBox(const std::vector<AABB> &bounds)
{
	Vec low(kInfinity, kInfinity, -kInfinity), high(-kInfinity, -kInfinity, kInfinity);
	for (size_t i = 0; i != bounds.size(); ++i) {
		if (bounds[i][0].x_ < low.x_) low.x_ = bounds[i][0].x_;
		if (bounds[i][0].y_ < low.y_) low.y_ = bounds[i][0].y_;
		if (bounds[i][0].z_ > low.z_) low.z_ = bounds[i][0].z_;

		if (bounds[i][1].x_ > high.x_) high.x_ = bounds[i][1].x_;
		if (bounds[i][1].y_ > high.y_) high.y_ = bounds[i][1].y_;
		if (bounds[i][1].z_ < high.z_) high.z_ = bounds[i][1].z_;
	}
	return AABB(low, high);
}

static AABB _calculateBounds(const std::vector<Object *> &objects, std::vector<AABB> &bounds)
{
	for (size_t i = 0; i != objects.size(); ++i)
		objects[i]->computeAABB(bounds[i][0], bounds[i][1]);
}

void BVH::build(const std::vector<Object *> &objects)
{
	std::vector<AABB> bounds(objects.size());
	_calculateBounds(objects, bounds);
	AABB box = _calculateBox(bounds);
	root_->split(box, bounds);
}
