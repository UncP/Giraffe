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

#include "random.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "ray.hpp"

class Camera
{
	public:
		Camera(const Vec &, const Vec &, const Vec & = Vec(0, 1, 0));

		virtual Ray computeRay(const double &, const double &) const = 0;

		virtual ~Camera() { }

	protected:
		Vec ori_;
		Vec dir_;
		Matrix worldToCamera_;
		Matrix cameraToWorld_;
};

class PerspectiveCamera : public Camera
{
	public:
		PerspectiveCamera(const Vec &, const Vec &, const Vec2 &, const Vec2 &, double &);

		Ray computeRay(const double &, const double &) const override;

		~PerspectiveCamera() { }

	private:
		Matrix rasterToCamera_;
};

class OrthographicCamera : public Camera
{
	public:
		OrthographicCamera(const Vec &, const Vec &, const Vec &up = Vec(0.0, 1.0, 0.0),
			const int &w = 100, const int &h = 100, const int &width = 512, const int &height = 512);

		Ray computeRay(const double &x, const double &y) const override;

		~OrthographicCamera() { }
	private:
		Matrix rasterToWorld_;
		Matrix worldToRaster_;

};

#endif /* _CAMERA_HPP_ */