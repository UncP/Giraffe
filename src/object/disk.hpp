/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-28 18:12:10
**/

#ifndef _DISK_HPP_
#define _DISK_HPP_

#include <memory>

#include "../core/object.hpp"
#include "../math/point.hpp"
#include "../math/matrix.hpp"

namespace Giraffe {

class Disk : public Object
{
	public:
		Disk(const Point3d &center, double radis1, double radis2, const Vector3d &axis,
			const std::shared_ptr<Texture> texture, const Matrix &matrix = Matrix::Identity)
		:center_(center), radis2_min_(radis1*radis1),
		 radis2_max_((radis1+2*radis2) * (radis1+2*radis2)), axis_(matrix(axis)), texture_(texture)
		{ }

		bool intersect(const Ray &ray, Isect &isect) const override;

		std::ostream& print(std::ostream &os) const override {
			return os << "disk\n" << center_ << axis_;
		}

	private:
		Point3d center_;
		double radis2_min_;
		double radis2_max_;
		Vector3d axis_;
		std::shared_ptr<Texture> texture_;
};

} // namespace Giraffe

#endif /* _DISK_HPP_ */