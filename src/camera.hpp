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

#include <time.h>
#include <random>

#include "vector.hpp"
#include "matrix.hpp"
#include "ray.hpp"

static const double fov = 0.5135;
static std::default_random_engine generator(time(0));
static std::uniform_real_distribution<double> distribution(0, 1);

class Camera
{
	public:
		Camera(const Vec3 &origin, const Vec3 &direction, const Vec3 &up = Vec3(0.0, 1.0, 0.0))
		:origin_(origin), direction_(direction), up_(up) {
			w_ = -direction_;
			normalize(w_);
			u_ = cross(up_, w_);
			normalize(u_);
			v_ = cross(w_, u_);
			normalize(v_);
			Matrix i;
			i.makeTransform(-origin_);
			matrix_ = Matrix(	u_.x_, v_.x_, w_.x_, 0,
												u_.y_, v_.y_, w_.y_, 0,
												u_.z_, v_.z_, w_.z_, 0,
												0,     0,     0,     1);
			matrix_ *= i;
		}

		const Vec3& origin()		const { return origin_; }
		const Vec3& direction() const { return direction_; }

		void computeRay(const int width, const int height, const int sx, const int sy,
										const int x, const int y, Ray &ray) const {
			double a = distribution(generator);
			double b = distribution(generator);
			a = a < 1 ? std::sqrt(a) - 1 : 1 - std::sqrt(2 - a);
			b = b < 1 ? std::sqrt(b) - 1 : 1 - std::sqrt(2 - b);
			ray.dir_ = Vec3(((((sx + 0.5 + a) / 2 + x) / width ) - 0.5) * fov,
								 			((((sy + 0.5 + b) / 2 + y) / height) - 0.5) * fov,
								 			direction_.z_);
			normalize(ray.dir_);
			ray.origin_ = origin_ + 100 * ray.dir_;
		}

		~Camera() { }

	private:
		Vec3 u_, v_, w_;
		Vec3 origin_;
		Vec3 direction_;
		Vec3 up_;
		Matrix matrix_;
};

#endif /* _CAMERA_HPP_ */