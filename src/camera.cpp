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

	Matrix screenToNdc;
	screenToNdc.toNdc(Vec(-250, -250, 0), Vec(250, 250, -1000));

	double ratio = width / static_cast<double>(height);
	Matrix ndcToRaster;
	ndcToRaster.toRaster(width, height * ratio);

	Matrix cameraToRaster = ndcToRaster * screenToNdc * perspective;
	rasterToCamera_ = inverse(cameraToRaster);
	std::cout << rasterToCamera_;
}

void PerspectiveCamera::computeRay(const double &x, const double &y, Ray &ray) const
{
	ray.dir_ 		= rasterToCamera_ * Vec(x, y, 0);
	ray.dir_ 	 += direction_;
	ray.origin_ = origin_;
	normalize(ray.dir_);
}

ProjectiveCamera::ProjectiveCamera(	const Vec &origin,
																		const Vec &direction,
																		const Vec &up,
																		const int &lensRadius, const int &focalDistance,
																		const int &width, const int &height)
:Camera(origin, direction, up), lensRadius_(lensRadius), focalDistance_(focalDistance)
{
	Matrix screenToNdc;
	int n = 80;
	screenToNdc.toNdc(Vec(-n, -n, -1), Vec(n, n, -100));

	double ratio = width / static_cast<double>(height);
	Matrix ndcToRaster;
	ndcToRaster.toRaster(width, height * ratio);

	Matrix screenToRaster = ndcToRaster * screenToNdc;
	rasterToScreen_ = inverse(screenToRaster);
}

void ProjectiveCamera::computeRay(const double &x, const double &y, Ray &ray) const
{
	Vec pos = rasterToScreen_ * Vec(x, y, 0);
	Vec hit = pos + Vec(0.0, 0.0, -focalDistance_);

	ray.origin_ = Vec(lensRadius_ * Random2(), lensRadius_ * Random2(), 0);
	ray.dir_ = hit - ray.origin_;
	// ray.dir_ = Vec(0.0, 0.02, -1.0);
	normalize(ray.dir_);
}
