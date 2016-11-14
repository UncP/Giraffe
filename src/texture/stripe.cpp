/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:46:31
**/

#include "stripe.hpp"

namespace Giraffe {

Vector3d StripeTexture::evaluate(Vertex &vertex) const
{
	Point3d p(transform_(vertex.position()));
	double var = axis_ == Xaxis ? p.x_ : (axis_ == Yaxis ? p.y_ : p.z_);
	double t = (1.0 + std::sin((var * PI) * factor_)) * 0.5;
	return mix(color1_, color2_, t);
}

std::shared_ptr<Texture> createStripeTexture(Slice &slice)
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
	return std::shared_ptr<Texture>(new StripeTexture(color1, color2, axis, factor, matrix));
}

} // namespace Giraffe
