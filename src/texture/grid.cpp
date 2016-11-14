/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-08 11:38:30
**/

#include "grid.hpp"

namespace Giraffe {

Vector3d GridTexture::evaluate(Vertex &vertex) const
{
	Point3d p(transform_(vertex.position()));
	double fac1 = p.x_ * PI * factor_;
	double fac2 = p.y_ * PI * factor_;
	double t = std::sin(fac1) * std::sin(fac2);
	return mix(color1_, color2_, t);
}

std::shared_ptr<Texture> createGirdTexture(Slice &slice)
{
	Matrix matrix = Matrix::Identity;
	Vector3d color1 = slice.findVector();
	Vector3d color2 = slice.findVector();
	int axis = slice.findAxis();
	double factor = slice.findDouble();
	if (!slice.eof()) {
		matrix = slice.findMatrix();
		assert(slice.eof());
	}
	return std::shared_ptr<Texture>(new GridTexture(color1, color2, axis, factor, matrix));
}

} // namespace Giraffe
