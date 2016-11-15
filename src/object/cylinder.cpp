/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-20 22:58:45
**/

#include <cassert>

#include "cylinder.hpp"

namespace Giraffe {

Cylinder::Cylinder(	const Point3d &center1, const Point3d &center2, const double radis,
										const Material *material)
:center1_(center1), center2_(center2), radius_(radis), radius2_(radis * radis),
inv2radius_(1.0 / (2.0 * radis)), material_(material)
{
	assert(center1_ != center2_);
	axis_ = center2_ - center1_;
	tmax_ = axis_.length();
	axis_ = normalize(axis_);
}

void Cylinder::computeBox(std::vector<double> &near, std::vector<double> &far,
	const Vector3d *normal) const
{
	double max = tmax_ > radius_ ? tmax_ : radius_;
	Point3d center = Point3d(center1_ + center2_) * 0.5;
	for (size_t i = 0, end = near.size(); i != end; ++i) {
		double p = proj(center, normal[i]);
		double n = p - max;
		double f = p + max;
		if (n < near[i]) near[i] = n;
		if (f > far[i]) far[i] = f;
	}
}

bool Cylinder::hit(const Ray &ray, const double &distance) const
{
	Vector3d ab(center1_ - ray.origin());
	Vector3d n(normalize(cross(axis_, ray.direction())));
	double l_to_l = std::fabs(dot(ab, n));
	if (l_to_l > radius_) return false;

	double ad = dot(axis_, ray.direction());
	double fac = 1.0 / ad;
	double t1 = dot(center1_ - ray.origin(), axis_) * fac;
	double t2 = dot(center2_ - ray.origin(), axis_) * fac;
	if (t1 < 0 && t2 < 0) return false;

	double aa = 1.0 / dot(axis_, axis_);
	Vector3d co(center1_ - ray.origin());
	Vector3d M = (ad * aa) * axis_ - ray.direction();
	double coa = dot(co, axis_);
	Vector3d N = co - ((coa * aa) * axis_);

	double A = dot(M, M);
	double C = dot(N, N) - radius2_;
	double B = dot(M, N);
	double delta = B * B - A * C;
	if (delta < 0) return false;

	B = -B;
	A = 1.0 / A;
	delta = std::sqrt(delta);
	double d1 = (B + delta) * A;
	double d2 = (B - delta) * A;
	if (d1 < 0) return false;
	double dis = d2 < 0 ? d1 : d2;

	double t = (dis * ad - coa) * aa;
	if ((tmax_ * t) < 0 || t > tmax_) {
		bool flag = t1 < t2;
		double dis = flag ? t1 : t2;
		const Point3d &c = flag ? center1_ : center2_;
		Point3d hitPos = ray.origin() + ray.direction() * dis;
		if ((hitPos - c).length2() <= radius2_ && dis < distance)
			return true;
		return false;
	}

	if (dis < distance)
		return true;
	return false;
}

bool Cylinder::intersect(const Ray &ray, Isect &isect) const
{
	// 计算光线与圆柱的距离
	Vector3d ab(center1_ - ray.origin());
	Vector3d n(normalize(cross(axis_, ray.direction())));
	double l_to_l = std::fabs(dot(ab, n));
	if (l_to_l > radius_) return false;

	// 计算光线与圆柱底面的交点
	double ad = dot(axis_, ray.direction());
	double fac = 1.0 / ad;
	double t1 = dot(center1_ - ray.origin(), axis_) * fac;
	double t2 = dot(center2_ - ray.origin(), axis_) * fac;
	if (t1 < 0 && t2 < 0) return false;

	// 计算光线与曲面的交点
	// t` = (t * dot(a, d) - dot(c-o, a)) / dot(a, a)
	// (t * (dot(a, d) / dot(a, a) * a - d) + (c-o) - dot(c-o, a) / dot(a, a) * a)^2 = r^2

	double aa = 1.0 / dot(axis_, axis_);
	Vector3d co(center1_ - ray.origin());
	Vector3d M = (ad * aa) * axis_ - ray.direction();
	double coa = dot(co, axis_);
	Vector3d N = co - ((coa * aa) * axis_);

	double A = dot(M, M);
	double C = dot(N, N) - radius2_;
	double B = dot(M, N);
	double delta = B * B - A * C;
	if (delta < 0) return false;

	B = -B;
	A = 1.0 / A;
	delta = std::sqrt(delta);
	double d1 = (B + delta) * A;
	double d2 = (B - delta) * A;
	if (d1 < 0) return false;
	double dis = d2 < 0 ? d1 : d2;

	double t = (dis * ad - coa) * aa;
	// if (tmax_ < 0 && t > 0) return false;
	// if (tmax_ > 0 && t < 0) return false;
	if ((tmax_ * t) < 0 || t > tmax_) {
		// 判断光线是否与底面相交
		bool flag = t1 < t2;
		double dis = flag ? t1 : t2;
		const Point3d &c = flag ? center1_ : center2_;
		Point3d hitPos = ray.origin() + ray.direction() * dis;
		if ((hitPos - c).length2() <= radius2_ && dis < isect.distance()) {
			isect.update(dis, this, hitPos, flag ? -axis_ : axis_, Point2d(), material_);
			return true;
		}
		return false;
	}

	if (dis < isect.distance()) {
		Point3d hitPos = ray.origin() + ray.direction() * dis;
		Point3d cc(center1_ + t * axis_);
		Point2d uv;
		isect.update(dis, this, hitPos, hitPos-cc, uv, material_);
		return true;
	}
	return false;
}

} // namespace Giraffe
