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
		double n = p - radius_;
		double f = p + radius_;
		if (n < near[i]) near[i] = n;
		if (f > far[i]) far[i] = f;
	}
}

bool Sphere::hit(const Ray &ray, Isect &isect) const
{
	Vector3d l = center_ - ray.origin();
	double s = dot(l, ray.direction());
	double l2 = l.length2();
	if (s < 0 && l2 > radius2_)
		return false;
	double q2 = l2 - s * s;
	if (q2 > radius2_)
		return false;
	double q = std::sqrt(radius2_ - q2);
	double dis = l2 > radius2_ ? (s - q) : (s + q);
	if (dis < isect.distance()) {
		isect.update(dis, this);
		return true;
	}
	return false;
}

bool Sphere::intersect(const Ray &ray, Isect &isect) const
{
	Vector3d l = center_ - ray.origin();
	double s = dot(l, ray.direction());
	double l2 = l.length2();
	if (s < 0 && l2 > radius2_)
		return false;
	double q2 = l2 - s * s;
	if (q2 > radius2_)
		return false;
	double q = std::sqrt(radius2_ - q2);
	double dis = l2 > radius2_ ? (s - q) : (s + q);

	if (dis < isect.distance()) {
		Point3d hitPos(ray.origin() + ray.direction() * dis);

		Point2d uv((hitPos.x_-center_.x_+radius_) * inv2radius_,
							 (-hitPos.y_+center_.y_+radius_) * inv2radius_);

		// Point2d uv((std::atan2(hitPos.y_-center_.y_, hitPos.x_-center_.x_) + DOU_PI) * DOU_PI_INV,
							 // 1 - (std::acos((hitPos.z_-center_.z_) / radius_) * PI_INV));

		isect.update(dis, this, IntersectionInfo(hitPos, uv, hitPos-center_), texture_);
		return true;
	} else {
		return false;
	}
}

} // namespace Giraffe
