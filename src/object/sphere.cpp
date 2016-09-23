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
		double p = proj(center_, normal[i]);
		double n = p - radis_;
		double f = p + radis_;
		if (n < near[i]) near[i] = n;
		if (f > far[i]) far[i] = f;
	}
}

bool Sphere::intersect(const Ray &ray, Isect &isect) const
{
	Vector3d l = center_ - ray.origin();
	double s = dot(l, ray.direction());
	double l2 = l.length2();
	if (s < 0 && l2 > radis2_)
		return false;
	double q2 = l2 - s * s;
	if (q2 > radis2_)
		return false;
	double q = std::sqrt(radis2_ - q2);
	double dis = l2 > radis2_ ? (s - q) : (s + q);

	if (dis < isect.distance()) {
		Point3d hitPos(ray.origin() + ray.direction() * dis);

		Point2d uv((hitPos.x_-center_.x_+radis_) * inv2radis_,
							 (-hitPos.y_+center_.y_+radis_) * inv2radis_);

		// Point2d uv((std::atan2(hitPos.y_-center_.y_, hitPos.x_-center_.x_) + DOU_PI) * DOU_PI_INV,
							 // 1 - (std::acos((hitPos.z_-center_.z_) / radis_) * PI_INV));

		isect.update(dis, IntersectionInfo(hitPos, uv, hitPos-center_), texture_.get());
		return true;
	} else {
		return false;
	}
}

} // namespace Giraffe
