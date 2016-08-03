/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-28 14:55:33
**/

#include "camera.hpp"

Camera::Camera(const Vec &origin, const Vec &direction, const Vec &up)
:origin_(origin), direction_(direction), up_(up)
{
	w_ = -direction_;
	normalize(w_);
	u_ = cross(up_, w_);
	normalize(u_);
	v_ = cross(w_, u_);
	normalize(v_);
	worldToCamera_ = Matrix(u_.x_, v_.x_, w_.x_, -origin_.x_,
													u_.y_, v_.y_, w_.y_, -origin_.y_,
													u_.z_, v_.z_, w_.z_, -origin_.z_,
													0,     0,     0,     1);
	cameraToWorld_ = inverse(worldToCamera_);
}

PerspectiveCamera::PerspectiveCamera(	const Vec &origin,
																			const Vec &direction,
																			const Vec &up,
																			const int &width, const int &height,
																			const double &fov,
																			const int &near, const int &far)
:Camera(origin, direction, up)
{
	Matrix perspective;
	perspective.makePerspective(fov, near, far);

	Matrix toScreen = perspective * worldToCamera_;

	double ratio = width / static_cast<double>(height);
	Matrix worldToRaster =	scale(Vec(width, height * ratio, 1)) * translate(Vec(0.5, 0.5, 0)) *
													toScreen;

	rasterToWorld_ = inverse(worldToRaster);
}

Ray PerspectiveCamera::computeRay(const double &x, const double &y) const
{
	Vec dir = rasterToWorld_ * Vec(x, y, 0);
	dir.z_  = direction_.z_;
	Vec ori = origin_;
	normalize(dir);
	return Ray(ori, dir);
}

ProjectiveCamera::ProjectiveCamera(	const Vec &origin,
																		const Vec &direction,
																		const Vec &up,
																		const int &lensRadius, const int &focalDistance,
																		const int &width, const int &height)
:Camera(origin, direction, up), lensRadius_(lensRadius), focalDistance_(focalDistance)
{
	Matrix worldToNdc;
	int limit = 100;
	worldToNdc.toNdc(Vec(-limit, -limit, -1), Vec(limit, limit, -100));

	double ratio = width / static_cast<double>(height);
	Matrix ndcToRaster;
	ndcToRaster.toRaster(width, height * ratio);

	Matrix worldToRaster = ndcToRaster * worldToNdc;
	rasterToWorld_ = inverse(worldToRaster);
}

Ray ProjectiveCamera::computeRay(const double &x, const double &y) const
{
	Vec pos = rasterToWorld_ * Vec(x, y, 0);
	pos.z_ = 0;
	Vec hit = pos + Vec(0.0, 0.0, -focalDistance_);
	Vec ori = Vec(lensRadius_ * Random2(), lensRadius_ * Random2(), 0);
	Vec dir = hit - ori;
	normalize(dir);
	return Ray(ori, dir);
}
