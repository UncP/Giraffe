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
	axis_ = normalize(center2_ - center1_);
}

bool Cylinder::intersect(const Ray &ray, Isect &isect) const
{
	// 计算光线与圆柱的距离
	Vector3d ab(center1_ - ray.origin());
	Vector3d n(normalize(cross(axis_, ray.direction())));
	double l_to_l = std::fabs(dot(ab, n));
	if (l_to_l > radis_) return false;

	// 计算光线与圆柱底面的交点
	double fac = 1.0 / dot(ray.direction(), axis_);
	double t1 = dot(center1_ - ray.origin(), axis_) * fac;
	double t2 = dot(center2_ - ray.origin(), axis_) * fac;
	if (t1 < kEpsilon) t1 = kInfinity;
	if (t2 < kEpsilon) t2 = kInfinity;

	if (t1 == t2) return false;

	bool flag = t1 < t2;
	double dis = flag ? t1 : t2;
	const Point3d &c = flag ? center1_ : center2_;
	// Vector3d normal = flag ? -axis_ : axis_;

	Point3d ori(ray.origin() + ray.direction() * dis);

	// 判断光线是否与底面相交
	Vector3d v(ori - c);
	if (dot(v, v) <= radis2_ && dis < isect.distance()) {
		Point2d uv;
		// Point2d uv((ori.x_-c.x_+radis_) * inv2radis_,
		// 					 (-ori.y_+c.y_+radis_) * inv2radis_);
		isect.update(dis, IntersectionInfo(ori, uv, flag ? -axis_ : axis_), texture_.get());
	}

	// 计算光线与曲面的交点

	return false;
}

} // namespace Giraffe
