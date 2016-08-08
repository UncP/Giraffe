/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-28 14:55:33
**/

#include "camera.hpp"

Camera::Camera(const Vec &ori, const Vec &dir, const Vec &up)
:ori_(ori), dir_(dir)
{
	Vec w = -dir_;
	normalize(w);
	Vec u = cross(up, w);
	normalize(u);
	Vec v = cross(w, u);
	normalize(v);
	worldToCamera_ = Matrix(u.x_, v.x_, w.x_, -origin_.x_,
													u.y_, v.y_, w.y_, -origin_.y_,
													u.z_, v.z_, w.z_, -origin_.z_,
													0,     0,     0,     1);
	cameraToWorld_ = inverse(worldToCamera_);
}

PerspectiveCamera::PerspectiveCamera(	const Vec &ori,
																			const Vec &dir,
																			const Vec2 &screen;
																			const Vec2 &film,
																			const double &fov)
:Camera(ori, dir)
{
	Matrix cameraToScreen = perspective(fov, near, far);

	Matrix screenToRaster =	scale(Vec(film.x_, film.y_, 1)) *
													scale(1.0/screen.x_, -1.0/screen.y_, 1) *
													transform(Vec(0.5, -0.5, 0));

	Matrix cameraToRaster = cameraToScreen * screenToRaster;
	rasterToCamera_ = inverse(cameraToRaster);
}

Ray PerspectiveCamera::computeRay(const double &x, const double &y) const
{
	Vec dir = rasterToCamera_(Vec(x, y, 0));
	Ray ray(Vec(0, 0, 0), normalize(dir));
	return cameraToWorld_(ray);
}

/*
OrthographicCamera::OrthographicCamera(	const Vec &origin,
																				const Vec &direction,
																				const Vec &up,
																				const int &w, const int &h,
																				const int &width, const int &height)
:Camera(origin, direction, up)
{
	Matrix cameraToNdc;
	cameraToNdc.toNdc(Vec(-w/2, -h/2, -1), Vec(w/2, h/2, -2));

	double ratio = width / static_cast<double>(height);
	Matrix ndcToRaster;
	ndcToRaster.toRaster(width, height * ratio);

	Matrix worldToRaster = ndcToRaster * cameraToNdc * worldToCamera_;
	rasterToWorld_ = inverse(worldToRaster);
	// Vec a1(0, 0, 0), a2(512, 512, 0);
	// std::cout << rasterToWorld_;
	// Vec b1 = rasterToWorld_ * a1;
	// Vec b2 = rasterToWorld_ * a2;
	// std::cout << b1 << b2;
}

Ray OrthographicCamera::computeRay(const double &x, const double &y) const
{
	Vec ori = rasterToWorld_ * Vec(x, y, 0);
	ori.z_ = origin_.z_;
	Vec dir = direction_;
	normalize(dir);
	return Ray(ori, dir);
}
*/