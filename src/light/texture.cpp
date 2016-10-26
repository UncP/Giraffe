/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-21 13:47:50
**/

#include <iostream>

#include "texture.hpp"

namespace Giraffe {

TextureLight::TextureLight(const Point3d &position, const Vector3d &direction,
	const Vector3d &intensity, double angle, const std::shared_ptr<Texture> &texture)
:Light(intensity), position_(position), direction_(-normalize(direction)),
 cos_max_(std::cos(radian(angle))), texture_(texture.get()) {
	center_ = position_ + direction_;
	radius_ = std::tan(radian(angle));
	inv2radius_ = 0.5 / radius_;
}

Vector3d TextureLight::sample(Isect &isect) const
{
	Vector3d vec(position_ - isect.position());
	double dis = vec.length();
	vec /= dis;
	if (dot(direction_, vec) > cos_max_) {
		isect.setDistance(dis);
		return vec;
	}
	return Vector3d(0);
}

Vector3d TextureLight::radiance(const Isect &isect) const
{
	Vector3d direction(normalize(position_ - isect.position()));
	double t = 1.0 / dot(direction_, direction);
	Vector3d p(position_ + t * direction);
	Point2d uv((p.x_-center_.x_+radius_)*inv2radius_, (-center_.y_+p.y_+radius_)*inv2radius_);
	IntersectionInfo surface(p, uv, Vector3d());
	return mult(intensity_, texture_->emission(surface));
}

} // namespace Giraffe
