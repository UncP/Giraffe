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

#include "../core/object.hpp"
#include "../math/vertex.hpp"

namespace Giraffe {

class Sphere : public Object
{
	public:
		Sphere(const Point3d &center, const double radis, const std::shared_ptr<Texture> &texture)
		:center_(center), radis_(radis), radis2_(radis * radis),
		 inv2radis_(1.0 / (2 * radis_)), texture_(texture) { }

		void computeBox(std::vector<double> &near, std::vector<double> &far,
			const Vector3d *normal) const override;

		bool intersect(const Ray &r, Isect &isect) const override;

		bool hit(const Ray &r) const override;

		bool emit() const override { return texture_->emit(); }

		std::ostream& print(std::ostream &os) const override { return os << "sphere\n" << center_; }

	private:
		Point3d 	center_;
		double 		radis_;
		double 		radis2_;
		double		inv2radis_;
		std::shared_ptr<Texture> texture_;
};

} // namespace Giraffe

#endif /* _SPHERE_HPP_ */