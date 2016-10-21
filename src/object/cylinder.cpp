/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-20 22:58:45
**/

#include "cylinder.hpp"

namespace Giraffe {

Cylinder::Cylinder(const Point3d &center1, const Point3d &center2, const double radis,
const std::shared_ptr<Texture> &texture)
:center1_(center1), center2_(center2), radis_(radis), radis2_(radis * radis),
inv2radis_(1.0 / (2.0 * radis)), texture_(texture)
{
	assert(center1_ != center2_);
	axis_ = center2_ - center1_;
	tmax_ = std::sqrt(dot(axis_, axis_));
	axis_ = normalize(axis_);
}

bool Cylinder::intersect(const Ray &ray, Isect &isect) const
{
	// 计算光线与圆柱的距离
	Vector3d ab(center1_ - ray.origin());
	Vector3d n(normalize(cross(axis_, ray.direction())));
	double l_to_l = std::fabs(dot(ab, n));
	if (l_to_l > radis_) return false;

	// 计算光线与圆柱底面的交点
	double ad = dot(axis_, ray.direction());
	double fac = 1.0 / ad;
	double t1 = dot(center1_ - ray.origin(), axis_) * fac;
	double t2 = dot(center2_ - ray.origin(), axis_) * fac;
	if (t1 < 0) t1 = kInfinity;
	if (t2 < 0) t2 = kInfinity;

	if (t1 == t2) return false;

	bool flag = t1 < t2;
	double dis = flag ? t1 : t2;
	const Point3d &c = flag ? center1_ : center2_;

	Point3d hitPos(ray.origin() + ray.direction() * dis);

	// 判断光线是否与底面相交
	Vector3d v(hitPos - c);
	if (v.length2() <= radis2_ && dis < isect.distance()) {
		Point2d uv;
		// Point2d uv((ori.x_-c.x_+radis_) * inv2radis_,
		// 					 (-ori.y_+c.y_+radis_) * inv2radis_);
		isect.update(dis, this,
			IntersectionInfo(hitPos, uv, flag ? -axis_ : axis_), texture_.get());
		return true;
	}

	// 计算光线与曲面的交点
	// t` = (t * dot(a, d) - dot(c-o, a)) / dot(a, a)
	// (t * (dot(a, d) / dot(a, a) * a - d) + (c-o) - dot(c-o, a) / dot(a, a) * a)^2 = r^2

	double aa = 1.0 / dot(axis_, axis_);
	Vector3d co(center1_ - ray.origin());
	Vector3d M = (ad * aa) * axis_ - ray.direction();
	double coa = dot(co, axis_);
	Vector3d N = co - ((coa * aa) * axis_);

	double A = dot(M, M);
	double C = dot(N, N) - radis2_;
	double B = dot(M, N);
	double delta = B * B - A * C;
	if (delta < 0) return false;

	B = -B;
	A = 1.0 / A;
	delta = std::sqrt(delta);
	double d1 = (B + delta) * A;
	double d2 = (B - delta) * A;
	if (d1 < 0) return false;
	if (d2 < 0)
		dis = d1;
	else
		dis = d2;

	double t = (dis * ad - coa) * aa;
	// if (tmax_ < 0 && t > 0) return false;
	// if (tmax_ > 0 && t < 0) return false;
	if ((tmax_ * t) < 0 || std::fabs(t) > tmax_) return false;

	if (dis < isect.distance()) {
		hitPos = ray.origin() + ray.direction() * dis;
		Point3d cc(center1_ + t * axis_);
		Point2d uv;
		isect.update(dis, this, IntersectionInfo(hitPos, uv, hitPos-cc), texture_.get());
		return true;
	}
	return false;
}

} // namespace Giraffe
