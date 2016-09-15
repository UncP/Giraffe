/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-06-24 15:22:09
**/

#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include <memory>

#include "object.hpp"

namespace Giraffe {

class Sphere : public Object
{
	public:
		Sphere(	const Point3d &center, const double radis, const std::shared_ptr<Texture> &texture)
		:c_(center), r_(radis), r2_(radis * radis), inv2r_(1.0 / (2 * r_)), texture_(texture) { }

		void computeBox(std::vector<double> &near, std::vector<double> &far,
			const Vector3d *normal) const override
		{
			for (size_t i = 0, end = near.size(); i != end; ++i) {
				double p = proj(c_, normal[i]);
				double n = p - r_;
				double f = p + r_;
				if (n < near[i]) near[i] = n;
				if (f > far[i]) far[i] = f;
			}
		}

		bool intersect(const Ray &r, Isect &isect) const override {
			Vector3d l = c_ - r.origin();
			double s = dot(l, r.direction());
			double l2 = l.length2();
			if (s < 0 && l2 > r2_)
				return false;
			double q2 = l2 - s * s;
			if (q2 > r2_)
				return false;
			double q = std::sqrt(r2_ - q2);
			double dis = l2 > r2_ ? (s - q) : (s + q);

			if (dis < isect.distance()) {
				Point3d hitPos(r.origin() + r.direction() * dis);
				Point2d uv((hitPos.x_-c_.x_+r_) * inv2r_, (-hitPos.y_+c_.y_+r_) * inv2r_);
				// Point2d uv((std::atan2(hitPos.y_-c_.y_, hitPos.x_-c_.x_) + DOU_PI) * DOU_PI_INV,
									 // 1 - (std::acos((hitPos.z_-c_.z_) / r_) * PI_INV));
				isect.update(dis, hitPos, hitPos - c_, uv, texture_.get());
			}
			return true;
		}

		std::ostream& print(std::ostream &os) const override { return os << "sphere\n" << c_; }

	private:
		Point3d 	c_;
		double 		r_;
		double 		r2_;
		double		inv2r_;
		std::shared_ptr<Texture> texture_;
};

} // namespace Giraffe

#endif /* _SPHERE_HPP_ */