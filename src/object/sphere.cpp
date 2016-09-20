/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-04 19:29:25
**/

#include "sphere.hpp"

namespace Giraffe {

void Sphere::computeBox(std::vector<double> &near, std::vector<double> &far,
	const Vector3d *normal) const
{
	for (size_t i = 0, end = near.size(); i != end; ++i) {
		double p = proj(c_, normal[i]);
		double n = p - r_;
		double f = p + r_;
		if (n < near[i]) near[i] = n;
		if (f > far[i]) far[i] = f;
	}
}

bool Sphere::intersect(const Ray &r, Isect &isect) const
{
	Vector3d l = c_ - r.origin();
	double s = dot(l, r.direction());
	double l2 = l.length2();
	if (s < 0 && l2 > r2_)
		return false;
	double q2 = l2 - s * s;
	if (q2 > r2_)
		return false;
	double q = std::sqrt(r2_ - q2);
	double dis = l2 > r2_ ? (s - q) : (s + q);

	if (dis < isect.distance()) {
		Point3d hitPos(r.origin() + r.direction() * dis);

		Point2d uv((hitPos.x_-c_.x_+r_) * inv2r_, (-hitPos.y_+c_.y_+r_) * inv2r_);

		// Point2d uv((std::atan2(hitPos.y_-c_.y_, hitPos.x_-c_.x_) + DOU_PI) * DOU_PI_INV,
							 // 1 - (std::acos((hitPos.z_-c_.z_) / r_) * PI_INV));

		isect.update(dis, IntersectionInfo(hitPos, uv, hitPos-c_), texture_.get());
	}
	return true;
}

} // namespace Giraffe
