/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-07-28 14:55:33
**/

#include "../utility/random.hpp"
#include "camera.hpp"
#include "sampler.hpp"

namespace Giraffe {

Camera::Camera(const Point3d &ori, const Vector3d &dir, double radius, double focal_distance,
	const Vector3d &up):radius_(radius), focal_distance_(focal_distance), ori_(ori), dir_(dir)
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
																			double   fov,
																			double   radius,
																			double   focal_distance)
:Camera(ori, dir, radius, focal_distance)
{
	Matrix cameraToScreen = perspective(fov, 1, 1000);

	Matrix screenToRaster =	scale(film.x_, film.y_, 1)
												* scale(1.0/screen.x_, -1.0/screen.y_, 1)
												* transform(Vector3d(0.5, -0.5, 0));

	Matrix cameraToRaster = cameraToScreen * screenToRaster;
	rasterToCamera_ = inverse(cameraToRaster);
}

Ray PerspectiveCamera::generateRay(const Point2d &sample) const
{
	static RandomNumberGenerator rng;
	Point3d ori(0);
	Ray ray(ori, normalize(Vector3d(rasterToCamera_(Point3d(sample.x_, sample.y_, 0)))));

	if (focal_distance_ > 0) {
		Point2d tmp = Point2d(rng.Uniform2(), rng.Uniform2());
		ori = Point3d(tmp.x_, tmp.y_, 0) * radius_;
		double z = -(focal_distance_ / ray.direction().z_);
		Point3d hit(ray.direction() * z);
		ray.setDirection(normalize(hit - ori));
	}

	ray.setOrigin(cameraToWorld_(ori));
	return std::move(ray);
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

} // namespace Giraffe
