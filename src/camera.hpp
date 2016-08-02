/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-25 23:16:00
**/

#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "vector.hpp"
#include "matrix.hpp"
#include "ray.hpp"

class Camera
{
	public:
		Camera(const Vec &origin, const Vec &direction, const Vec &up);

		virtual void computeRay(const double &, const double &, Ray &) const = 0;

		virtual ~Camera() { }

	protected:
		Vec origin_;
		Vec direction_;
		Vec up_;
		Vec u_, v_, w_;
		Matrix worldToCamera_;
		Matrix cameraToWorld_;
		Matrix rasterToWorld_;
};

class PerspectiveCamera : public Camera
{
	public:
		PerspectiveCamera(const Vec &, const Vec &, const Vec &up = Vec(0.0, 1.0, 0.0),
			const int &width = 512, const int &height = 512,
			const double &fov = 60.0, const int &near = 1, const int &far = 1000);

		void computeRay(const double &, const double &, Ray &) const;

		~PerspectiveCamera() { }

};

class ProjectiveCamera : public Camera
{
	public:
		ProjectiveCamera(const Vec &, const Vec &, const Vec &up = Vec(0.0, 1.0, 0.0),
			const int &lensRadius = 1, const int &focalDistance = 200,
			const int &width = 512, const int &height = 512);

		void computeRay(const double &x, const double &y, Ray &ray) const override;

		const Matrix& rasterToWorld() const { return rasterToWorld_; }

		~ProjectiveCamera() { }

	private:
		int lensRadius_;
		int focalDistance_;
};

#endif /* _CAMERA_HPP_ */