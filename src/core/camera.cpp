/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-28 14:55:33
**/

#include "camera.hpp"

Camera::Camera(const Point3d &ori, const Vector3d &dir, const Vector3d &up)
:ori_(ori), dir_(dir)
{
	Vector3d w = -dir_;
	normalize(w);
	Vector3d u = cross(up, w);
	normalize(u);
	Vector3d v = cross(w, u);
	normalize(v);
	worldToCamera_ = Matrix(u.x_, v.x_, w.x_, -ori_.x_,
													u.y_, v.y_, w.y_, -ori_.y_,
													u.z_, v.z_, w.z_, -ori_.z_,
													0,     0,     0,     1);
	cameraToWorld_ = inverse(worldToCamera_);
}

PerspectiveCamera::PerspectiveCamera(	const Point3d  &ori,
																			const Vector3d &dir,
																			const Point2i &screen,
																			const Point2i &film,
																			const double   fov)
:Camera(ori, dir)
{
	Matrix cameraToScreen = perspective(fov, 1, 1000);

	// std::cout << cameraToScreen;

	Matrix screenToRaster =	scale(film.x_, film.y_, 1)
												* scale(1.0/screen.x_, -1.0/screen.y_, 1)
												* transform(Vector3d(0.5, -0.5, 0));

	Matrix cameraToRaster = cameraToScreen * screenToRaster;
	rasterToCamera_ = inverse(cameraToRaster);

	// std::cout << rasterToCamera_;

	// Vector3d d1 = normalize(Vector3d(rasterToCamera_(Point3d(0, 0, 0))));
	// std::cout << d1;
	// Vector3d d2 = normalize(Vector3d(rasterToCamera_(Point3d(1, 0, 0))));
	// std::cout << d2;
	// Vector3d d3 = normalize(Vector3d(rasterToCamera_(Point3d(0, 1, 0))));
	// std::cout << d3;
	// Vector3d d4 = normalize(Vector3d(rasterToCamera_(Point3d(1, 1, 0))));
	// std::cout << d4;
}

Ray PerspectiveCamera::generateRay(const Point2d &sample) const
{
	return Ray(	cameraToWorld_(Point3d(0)),
							normalize(Vector3d(rasterToCamera_(Point3d(sample.x_, sample.y_, 0)))));
}

/*
OrthographicCamera::OrthographicCamera(	const Vector3d &origin,
																				const Vector3d &direction,
																				const Vector3d &up,
																				const int &w, const int &h,
																				const int &width, const int &height)
:Camera(origin, direction, up)
{
	Matrix cameraToNdc;
	cameraToNdc.toNdc(Vector3d(-w/2, -h/2, -1), Vector3d(w/2, h/2, -2));

	double ratio = width / static_cast<double>(height);
	Matrix ndcToRaster;
	ndcToRaster.toRaster(width, height * ratio);

	Matrix worldToRaster = ndcToRaster * cameraToNdc * worldToCamera_;
	rasterToWorld_ = inverse(worldToRaster);
	// Vector3d a1(0, 0, 0), a2(512, 512, 0);
	// std::cout << rasterToWorld_;
	// Vector3d b1 = rasterToWorld_ * a1;
	// Vector3d b2 = rasterToWorld_ * a2;
	// std::cout << b1 << b2;
}

Ray OrthographicCamera::computeRay(const double &x, const double &y) const
{
	Vector3d ori = rasterToWorld_ * Vector3d(x, y, 0);
	ori.z_ = origin_.z_;
	Vector3d dir = direction_;
	normalize(dir);
	return Ray(ori, dir);
}
*/