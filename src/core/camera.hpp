/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-07-25 23:16:00
**/

#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "../math/matrix.hpp"
#include "../math/ray.hpp"

namespace Giraffe {

class Camera
{
	public:
		Camera(	const Point3d &, const Vector3d &, double radius, double focal_distance,
						const Vector3d & = Vector3d(0, 1, 0));

		virtual Ray generateRay(const Point2d &) const = 0;

		virtual ~Camera() { }

	protected:
		double radius_;
		double focal_distance_;
		Point3d	 ori_;
		Vector3d dir_;
		Matrix worldToCamera_;
		Matrix cameraToWorld_;
};

class PerspectiveCamera : public Camera
{
	public:
		PerspectiveCamera(const Point3d &, const Vector3d &,
											const Point2i &, const Point2i &, double, double = 0, double = 0);

		Ray generateRay(const Point2d &) const override;

	private:
		Matrix rasterToCamera_;
};

/*
class OrthographicCamera : public Camera
{
	public:
		OrthographicCamera(const Vector3d &, const Vector3d &,
			const int &w = 100, const int &h = 100, const int &width = 512, const int &height = 512);

		Ray generateRay(const Point2d &) const override;

	private:
};
*/

} // namespace Giraffe

#endif /* _CAMERA_HPP_ */