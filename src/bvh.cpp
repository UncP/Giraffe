/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-01 15:21:29
**/

#include "bvh.hpp"

static bool _intersect(const double &o, const double &d, const double &f,
	const double &s, const double &b, double &tmin, double &tmax)
{
	double parallel = std::fabs(d);
	if (parallel < kParallel) {
		if (o < s || o > b) return false;
	} else {
		double min, max;
		min = (s - o) * f;
		max = (b - o) * f;
		if (min > max) std::swap(min, max);
		if (max < 0) return false;
		if (min > tmin) tmin = min;
		if (max < tmax) tmax = max;
		if (tmin > tmax) return false;
	}
	return true;
}

bool AABB::intersect(const Ray &ray, Isect &isect) const
{
	double tmin = -kInfinity, tmax = kInfinity;
	if (!_intersect(ray.ori_.x_, ray.dir_.x_, ray.inv_.x_, lbf_.x_, rtn_.x_, tmin, tmax))
		return false;
	if (!_intersect(ray.ori_.y_, ray.dir_.y_, ray.inv_.y_, lbf_.y_, rtn_.y_, tmin, tmax))
		return false;
	if (!_intersect(ray.ori_.z_, ray.dir_.z_, ray.inv_.z_, lbf_.z_, rtn_.z_, tmin, tmax))
		return false;

	return true;
}

bool BVHNode::intersect(const Ray &ray, Isect &isect) const
{
	if (!obj_->intersect(ray, isect))
		return false;

	if (!left_) return true;

	bool l = left_-> intersect(ray, isect);
	bool r = right_->intersect(ray, isect);
	return l || r;
}

bool BVH::intersect(const Ray &ray, Isect &isect) const
{
	return root_->intersect(ray, isect);
}

static AABB _calculateBoundsBox(const std::vector<Object *> &objects, std::vector<AABB> &bounds)
{
	Vec low(kInfinity), high(-kInfinity);
	for (size_t i = 0; i != objects.size(); ++i) {
		objects[i]->computeAABB(bounds[i][0], bounds[i][1]);

		if (bounds[i][0].x_ < low.x_) low.x_ = bounds[i][0].x_;
		if (bounds[i][0].y_ < low.y_) low.y_ = bounds[i][0].y_;
		if (bounds[i][0].z_ < low.z_) low.z_ = bounds[i][0].z_;

		if (bounds[i][1].x_ > high.x_) high.x_ = bounds[i][1].x_;
		if (bounds[i][1].y_ > high.y_) high.y_ = bounds[i][1].y_;
		if (bounds[i][1].z_ > high.z_) high.z_ = bounds[i][1].z_;
	}
	return AABB(low, high);
}

static inline void _sortByPlane(std::vector<Object*> &objects, std::vector<AABB> &box,
	const Plane &p)
{
	std::sort(box.begin(), box.end(),
		[p](const AABB &m, const AABB &n) { return m[1][p] < n[1][p]; });
	std::sort(objects.begin(), objects.end(),
		[p](const Object *a, const Object *b) { return a->center()[p] < b->center()[p]; });
}

static int _splitByPlane(std::vector<Object*> &objects, std::vector<AABB> &bounds,
	const Plane &p)
{
	_sortByPlane(objects, bounds, p);
	double mid = (bounds[0][1][p] + bounds[bounds.size()-1][1][p]) / 2;
	auto it = find_if(bounds.begin(), bounds.end(),
		[mid, p](const AABB &box) { return box[1][p] > mid; });
	if (it == bounds.begin())
		return 1;
	if (it == bounds.end())
		return bounds.size() - 1;
	else
		return it - bounds.begin();
}

void BVHNode::split(const AABB &box, std::vector<Object *> &objects, std::vector<AABB> &bounds)
{
	if (objects.size() == 1) {
		obj_ = shared_ptr<Object>(objects[0]);
		return ;
	}

	obj_ = shared_ptr<Object>(new AABB(box));
	if (!obj_) {
		std::cerr << "BVH build failed :(\n";
		exit(-1);
	}

	int pos = _splitByPlane(objects, bounds, box.getSplitPlane());

	left_  = shared_ptr<BVHNode>(new BVHNode());
	if (!left_) {
		std::cerr << "BVH build failed :(\n";
		exit(-1);
	}

	right_ = shared_ptr<BVHNode>(new BVHNode());
	if (!right_) {
		std::cerr << "BVH build failed :(\n";
		exit(-1);
	}

	std::vector<Object*> lObjects(objects.begin(), objects.begin()+pos);
	std::vector<Object*> rObjects(objects.begin()+pos, objects.end());
	std::vector<AABB> lBounds(lObjects.size()), rBounds(rObjects.size());
	AABB lBox = _calculateBoundsBox(lObjects, lBounds);
	AABB rBox = _calculateBoundsBox(rObjects, rBounds);
	left_	->split(lBox, lObjects, lBounds);
	right_->split(rBox, rObjects, rBounds);
}

void BVH::build(std::vector<Object *> &objects)
{
	std::vector<AABB> bounds(objects.size());
	AABB box = _calculateBoundsBox(objects, bounds);
	root_->split(box, objects, bounds);
}

void BVHNode::traverse()
{
	if (obj_)
		obj_->print();
	else
		return ;
	if (left_ ) left_-> traverse();
	if (right_) right_->traverse();
}

void BVH::print() const
{
	root_->traverse();
}
