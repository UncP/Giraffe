/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:51:17
**/

#include "brick.hpp"

namespace Giraffe {

Vector3d BrickTexture::evaluate(Vertex &vertex) const
{
	Point2d uv_(transform_(vertex.uv()));
	double ss = uv_.x_ / width_;
	double tt = uv_.y_ / height_;

	if (std::fmod(tt * 0.5, 1.0) > 0.5)
		ss += 0.5;

	double sbrick = std::floor(ss);
	double tbrick = std::floor(tt);

	ss -= sbrick;
	tt -= tbrick;

	double w = step(wf_, ss) - step(1 - wf_, ss);
	double h = step(hf_, tt) - step(1 - hf_, tt);

	return mix(color1_, color2_, w * h);
}

std::shared_ptr<Texture> createBrickTexture(Slice &slice)
{
	Vector3d color1 = slice.findVector();
	Vector3d color2 = slice.findVector();
	double width = slice.findDouble();
	double height = slice.findDouble();
	double interval = slice.findDouble();
	assert(slice.eof());
	return std::shared_ptr<Texture>(new BrickTexture(color1, color2, width, height, interval));
}

} // namespace Giraffe
