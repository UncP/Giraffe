/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-15 11:21:15
**/

#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <memory>
#include <array>
#include <map>

#include "object.hpp"

namespace Giraffe {

class Cube : public Object
{
	public:

		typedef std::array<std::pair<double, double>, 3> box;

		Cube(	const Point3d &center, int length, int width, int height,
					const std::shared_ptr<Texture> &texture);

		bool intersect(const Ray &, Isect &) const override;

		std::ostream& print(std::ostream &os) const override {
			for (auto e : vertices_) os << e;
			for (auto e : normals_)  os << e;
			for (auto each : bounds_)
				for (auto e : each)
					os << e.first << " " << e.second << std::endl;
			return os;
		}

	private:
		std::vector<Point3d>            vertices_;
		std::vector<Vector3d>           normals_;
		std::array<box, 6>              bounds_;
		std::shared_ptr<Texture>        texture_;

		static std::array<std::array<int, 4>, 6> indexes_;

		void computeNormals();
		void computeBounds();
};

} // namespace Giraffe

#endif /* _CUBE_HPP_ */