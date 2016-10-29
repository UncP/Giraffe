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

#include <array>
#include <map>

#include "../core/object.hpp"
#include "../accelerator/bvh.hpp"
#include "../math/matrix.hpp"

namespace Giraffe {

class Cube : public Object
{
	public:
		typedef std::array<std::pair<double, double>, 3> box;

		typedef std::array<int, 4> quad;

		Cube( const Point3d &center, int length, int width, int height,
					const Texture *texture, const Matrix &matrix = Matrix::Identity);

		bool intersect(const Ray &, Isect &) const override;

		std::ostream& print(std::ostream &os) const override;

		~Cube() { delete aabb_; }

	private:
		std::vector<Point3d>   vertices_;
		std::vector<Vector3d>  normals_;
		std::array<box, 6>     bounds_;
		const Texture         *texture_;
		Box                   *aabb_;

		const static std::array<quad, 6> indexes_;

		void computeNormals();
		void computeBounds();
};

} // namespace Giraffe

#endif /* _CUBE_HPP_ */