/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-01 15:21:29
**/

#include "bvh.hpp"

static bool _intersect(const double &o, const double &f,
	const double &s, const double &b, double &tmin, double &tmax)
{
	double min, max;
	min = (s - o) * f;
	max = (b - o) * f;
	if (f < 0) std::swap(min, max);
	if (max < 0) return false;
	if (min > tmin) tmin = min;
	if (max < tmax) tmax = max;
	if (tmin > tmax) return false;
	return true;
}

bool Box::intersect(const Ray &ray, Isect &isect) const
{
	double near = -kInfinity, far = kInfinity;
	for (size_t i = 0, end = near_.size(); i != end; ++i) {
		if (!_intersect(ray.no_[i], ray.nd_[i], near_[i], far_[i], near, far))
			return false;
	}
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

static void _calculateBounds(const std::vector<Object *> &objects, std::vector<Box *> &boxes,
	Box *box)
{
	for (size_t i = 0, iEnd = objects.size(); i != iEnd; ++i) {
		objects[i]->computeBox(boxes[i]->near_, boxes[i]->far_, NormalSet);
		for (size_t j = 0, jEnd = box->size(); j != jEnd; ++j) {
			if (boxes[i]->near_[j] < box->near_[j]) box->near_[j] = boxes[i]->near_[j];
			if (boxes[i]->far_[j] > box->far_[j]) box->far_[j] = boxes[i]->far_[j];
		}
	}
}

static inline void _sortByPlane(std::vector<Object *> &objects, std::vector<Box *> &boxes,
	const Plane &p)
{
	// std::sort(boxes.begin(), boxes.end(),
	// 	[p](const Box *m, const Box *n) { return m->far_[p] < n->far_[p]; });
	// std::sort(objects.begin(), objects.end(),
	// 	[p](const Object *a, const Object *b) { return a->center()[p] < b->center()[p]; });
}

static int _splitByPlane(std::vector<Object *> &objects, std::vector<Box *> &boxes,
	const Plane &p)
{
	_sortByPlane(objects, boxes, p);
	double mid = (boxes[0]->far_[p] + boxes[boxes.size()-1]->far_[p]) / 2;
	auto it = std::find_if(boxes.begin(), boxes.end(),
		[mid, p](const Box *box) { return box->far_[p] > mid; });
	if (it == boxes.begin())
		return 1;
	if (it == boxes.end())
		return boxes.size() - 1;
	else
		return it - boxes.begin();
}

void BVHNode::split(Box *box, std::vector<Object *> &objects, std::vector<Box *> &boxes)
{
	if (objects.size() == 1) {
		obj_ = std::shared_ptr<Object>(objects[0]);
		delete box;
		return ;
	}

	obj_ = std::shared_ptr<Object>(box);

	int pos = _splitByPlane(objects, boxes, box->getSplitPlane());

	left_  = std::shared_ptr<BVHNode>(new BVHNode());
	if (!left_) {
		std::cerr << "building BVH failed :(\n";
		exit(-1);
	}

	right_ = std::shared_ptr<BVHNode>(new BVHNode());
	if (!right_) {
		std::cerr << "building BVH failed :(\n";
		exit(-1);
	}

	std::vector<Object*> lObjects(objects.begin(), objects.begin()+pos);
	std::vector<Object*> rObjects(objects.begin()+pos, objects.end());
	std::vector<Box *> lBoxes(lObjects.size()), rBoxes(rObjects.size());
	for (size_t i = 0; i != lObjects.size(); ++i) lBoxes[i] = new AABB();
	Box *lBox = new AABB();
	_calculateBounds(lObjects, lBoxes, lBox);

	for (size_t i = 0; i != rObjects.size(); ++i) rBoxes[i] = new AABB();
	Box *rBox = new AABB();
	_calculateBounds(rObjects, rBoxes, rBox);

	left_	->split(lBox, lObjects, lBoxes);
	right_->split(rBox, rObjects, rBoxes);
	for (size_t i = 0; i != lBoxes.size(); ++i) delete lBoxes[i];
	for (size_t i = 0; i != rBoxes.size(); ++i) delete rBoxes[i];
}

void BVH::build(std::vector<Object *> &objects) {
	std::vector<Box *> boxes(objects.size());
	for (size_t i = 0; i != objects.size(); ++i) boxes[i] = new AABB();
	Box *box = new AABB();
	_calculateBounds(objects, boxes, box);
	root_->split(box, objects, boxes);
	for (size_t i = 0; i != boxes.size(); ++i) delete boxes[i];
}
