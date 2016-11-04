/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-01 15:21:29
**/

#include <map>
#include <algorithm>

#include "bvh.hpp"

namespace Giraffe {

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

static int _splitByPlane(std::vector<std::pair<Object *, Box *>> &boxes,
	const size_t beg, const size_t end, const Axis &p)
{
	std::sort(boxes.begin() + beg, boxes.begin() + end,
		[p](const std::pair<Object *, Box *> &p1, const std::pair<Object *, Box *> &p2)
		{ return p1.second->far(p) < p2.second->far(p); });

	double mid = (boxes[beg].second->far(p) + boxes[end-1].second->far(p)) / 2;

	auto it = std::find_if(boxes.begin() + beg, boxes.begin() + end,
		[mid, p](const std::pair<Object *, Box *> &pp) { return pp.second->far(p) > mid; });

	if (it == (boxes.begin() + beg))
		return 1;
	if (it == (boxes.begin() + end))
		return end - 1;
	else
		return it - (boxes.begin() + beg);
}

void BVHNode::split(Box *box, std::vector<std::pair<Object *, Box *>> &boxes,
	const size_t beg, const size_t end)
{
	if ((end - beg) == 1) {
		obj_ = boxes[beg].first;
		delete box;
		return ;
	}

	obj_ = box;
	int pos = _splitByPlane(boxes, beg, end, box->getSplitPlane());
	left_  = std::shared_ptr<BVHNode>(new BVHNode());
	right_ = std::shared_ptr<BVHNode>(new BVHNode());

	Box *lBox = new AABB();
	lBox->enclose(boxes, beg, beg + pos);
	left_	->split(lBox, boxes, beg, beg + pos);

	Box *rBox = new AABB();
	rBox->enclose(boxes, beg + pos, end);
	right_->split(rBox, boxes, beg + pos, end);
}

void BVH::build(std::vector<Object *> &objects)
{
	std::vector<std::pair<Object *, Box *>> boxes(objects.size());
	Box *tmp = new AABB[boxes.size()];

	for (size_t i = 0; i != objects.size(); ++i) {
		boxes[i].first 	= objects[i];
		boxes[i].second = &tmp[i];
		boxes[i].first->computeBox(boxes[i].second->near(), boxes[i].second->far(), Box::NormalSet);
	}

	Box *box = new AABB();
	box->enclose(boxes, 0, boxes.size());

	root_->split(box, boxes, 0, boxes.size());

	delete [] tmp;
}

} // namespace Giraffe
