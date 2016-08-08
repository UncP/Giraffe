/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-04 19:29:25
**/

#include "sphere.hpp"

void Sphere::computeBox(std::vector<double> &near, std::vector<double> &far,
	const Vec *normal) const
{
	for (size_t i = 0, end = near.size(); i != end; ++i) {
		double p = dot(c_, normal[i]);
		double n = p - r_;
		double f = p + r_;
		if (n < near[i]) near[i] = n;
		if (f > far[i]) far[i] = f;
	}
}

bool Sphere::intersect(const Ray &r, Isect &isect) const {
	Vec l = c_ - r.ori_;
	double s = dot(l, r.dir_);
	double l2 = l.length2();
	if (s < 0 && l2 > r2_)
		return false;
	double q2 = l2 - s * s;
	if (q2 > r2_)
		return false;
	double q = std::sqrt(r2_ - q2);
	double dis = l2 > r2_ ? (s - q) : (s + q);

	if (dis < isect.dis_) {
		Vec hitPos = r.ori_;
		hitPos += r.dir_ * dis;
		isect.update(dis, this, hitPos, hitPos - c_, refl_, color_, emit_, emission_);
	}
	return true;
}

bool DynamicSphere::intersect(const Ray &r, Isect &isect) const {

	Vec off = shift_ * Ray::Time;
	Vec l = (c_ + off) - r.ori_;

	// Vec l = c_ - r.ori_;
	double s = dot(l, r.dir_);
	double l2 = l.length2();
	if (s < 0 && l2 > r2_)
		return false;
	double q2 = l2 - s * s;
	if (q2 > r2_)
		return false;
	double q = std::sqrt(r2_ - q2);
	double dis = l2 > r2_ ? (s - q) : (s + q);

	if (dis < isect.dis_) {
		Vec hitPos = r.ori_;
		hitPos += r.dir_ * dis;
		isect.update(dis, this, hitPos, hitPos - c_, refl_, color_, emit_, emission_);
	}
	return true;
}
