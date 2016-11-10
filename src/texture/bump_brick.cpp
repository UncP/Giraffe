/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:54:47
**/

#include <assert.h>

#include "../math/matrix.hpp"
#include "bump_brick.hpp"

namespace Giraffe {

BumpBrickTexture::BumpBrickTexture(const Vector3d &color1, const Vector3d &color2,
double width, double height, double interval, double gradient)
:color1_(color1), color2_(color2), gradient_(gradient)
{
	width_  = width + interval;
	height_ = height + interval;
	wf_ = (interval * 0.5) / width;
	hf_ = (interval * 0.5) / height;
	generateHeightMap();
}

void BumpBrickTexture::showHeightMap()
{
	bool flag = true;
	for (int i = 0; i != map_len; ++i) {
		for (int j = 0; j != map_len; ++j) {
			if((i <= 15 && (j <= 15 || j >= 85)) || (i >= 85 && (j <= 15 || j >= 85))) {
				std::cout << static_cast<int>(height_map_[i * map_len + j]) << " ";
				flag = true;
			} else {
				flag = false;
			}
		}
		if (flag)
			std::cout << std::endl;
	}
}

void BumpBrickTexture::generateHeightMap()
{
	int width_count  = static_cast<int>(static_cast<double>(map_len) * wf_ + 0.5);
	int height_count = static_cast<int>(static_cast<double>(map_len) * hf_ + 0.5);
	int min_blank = std::min(width_count, height_count);
	int max_blank = std::max(width_count, height_count);
	int interval = (max_blank - 1) / (min_blank - 1);
	int max_fill = max_blank + 1;
	float k = -static_cast<float>(height_count) / static_cast<float>(width_count);
	for (int i = 0; i != map_len; ++i) {
		height_map_[i * map_len] = 1;
		height_map_[i] = 1;
		height_map_[(map_len-1) * map_len + i] = 1;
		height_map_[i * map_len + (map_len-1)] = 1;
	}
	for (int i = width_count; i != (map_len-width_count); ++i) {
		height_map_[(height_count-1) * map_len + i] = max_blank;
		height_map_[(map_len-height_count) * map_len + i] = max_blank;
	}
	for (int i = height_count; i != (map_len-height_count); ++i) {
		height_map_[i * map_len + (width_count-1)] = max_blank;
		height_map_[i * map_len + (map_len-width_count)] = max_blank;
	}
	for (int i = 1; i != height_count; ++i) {
		for (int j = 1; j != width_count; ++j) {
			int index = i * map_len + j;
			if (static_cast<float>(-i) > k * static_cast<float>(j)) {
				if (width_count > height_count) {
					height_map_[index] = height_map_[(i-1) * map_len + j] + interval;
					if (height_map_[index] < height_map_[index-1])
						height_map_[index] = height_map_[index-1];
				} else {
					height_map_[index] = height_map_[(i-1) * map_len + j] + 1;
				}
			} else {
				if (width_count > height_count) {
					height_map_[index] = height_map_[i * map_len + (j-1)] + 1;
				} else {
					height_map_[index] = height_map_[i * map_len + (j-1)] + interval;
				}
			}
			height_map_[i * map_len + (map_len-j-1)] = height_map_[index];
			height_map_[(map_len-i-1) * map_len + j] = height_map_[index];
			height_map_[(map_len-i-1) * map_len + (map_len-j-1)] = height_map_[index];
		}
	}
	height_map_[(width_count-1) + (height_count-1) * map_len] = max_blank;
	height_map_[(map_len-width_count) + (height_count-1) * map_len] = max_blank;
	height_map_[(width_count-1) + (map_len-height_count) * map_len] = max_blank;
	height_map_[(map_len-width_count) + (map_len-height_count) * map_len] = max_blank;
	for (int i = 1; i != height_count; ++i) {
		char val = height_map_[i * map_len + (width_count-1)];
		for (int j = width_count; j != map_len-width_count; ++j) {
			height_map_[i * map_len + j] = val;
			height_map_[(map_len-i-1) * map_len + j] = val;
		}
	}
	for (int i = 1; i != width_count; ++i) {
		char val = height_map_[(height_count-1) * map_len + i];
		for (int j = height_count; j != map_len-height_count; ++j) {
			height_map_[j * map_len + i] = val;
			height_map_[j * map_len + (map_len-i-1)] = val;
		}
	}
	for (int i = height_count; i != map_len-height_count; ++i)
		for (int j = width_count; j != map_len-width_count; ++j)
			height_map_[i * map_len + j] = max_fill;
}

Vector3d BumpBrickTexture::evaluate(Vertex &vertex) const
{
	double ss = vertex.uv().x_ / width_;
	double tt = vertex.uv().y_ / height_;

	if (std::fmod(tt * 0.5, 1.0) > 0.5)
		ss += 0.5;

	double sbrick = std::floor(ss);
	double tbrick = std::floor(tt);

	ss -= sbrick;
	tt -= tbrick;

	double w = step(wf_, ss) - step(1 - wf_, ss);
	double h = step(hf_, tt) - step(1 - hf_, tt);
	double gap = w * h;
	if (gap == 0.0) {
		int i = ss * (map_len - 1);
		int j = tt * (map_len - 1);
		int l, r;
		if (i < (map_len-1)) l = i, r = i + 1;
		else l = i - 1, r = i;
		double du = gradient_ * (height_map_[j * map_len + r] - height_map_[j * map_len + l]);
		double angle1 = rradian(std::atan(du));
		Matrix a = rotateY(angle1);
		int u, d;
		if (j < (map_len-1)) u = j, d = j + 1;
		else u = j - 1, d = j;
		double dv = gradient_ * (height_map_[u * map_len + i] - height_map_[d * map_len + i]);
		double angle2 = rradian(std::atan(dv));
		Matrix b = rotateX(angle2);
		Matrix c = a * b;
		vertex.setNormal(c(vertex.normal()));
	}
	return mix(color1_, color2_, gap);
}

} // namespace Giraffe
