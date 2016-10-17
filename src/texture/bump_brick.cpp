/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:54:47
**/

#include <assert.h>

#include "bump_brick.hpp"

namespace Giraffe {

BumpBrickTexture::BumpBrickTexture(const Vector3d &color1, const Vector3d &color2,
double width, double height, double interval, bool emit, REFL refl)
:Texture(refl, emit), color1_(color1), color2_(color2)
{
	assert(width > 0 && height > 0 && interval > 0);
	width_  = width + interval;
	height_ = height + interval;
	wf_ = (interval * 0.5) / width;
	hf_ = (interval * 0.5) / height;
	generateHeightMap();
	// showHeightMap();
}

void BumpBrickTexture::showHeightMap()
{
	bool flag = true;
	for (int i = 0; i != map_len; ++i) {
		for (int j = 0; j != map_len; ++j) {
			if((i <= 20 && (j <= 20 || j >= 80)) || (i >= 80 && (j <= 20 || j >= 80))) {
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
	// std::cout << width_count << " " << height_count << std::endl;
	int min_blank = std::min(width_count, height_count);
	int max_blank = std::max(width_count, height_count);
	int interval = (max_blank - 1) / (min_blank - 1);
	// std::cout << interval << std::endl;
	int max_fill = max_blank + 1;
	// std::cout << max_fill << std::endl;
	float k = -static_cast<float>(height_count) / static_cast<float>(width_count);
	// std::cout << k << std::endl;
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
		unsigned char val = height_map_[i * map_len + (width_count-1)];
		for (int j = width_count; j != map_len-width_count; ++j) {
			height_map_[i * map_len + j] = val;
			height_map_[(map_len-i-1) * map_len + j] = val;
		}
	}
	for (int i = 1; i != width_count; ++i) {
		unsigned char val = height_map_[(height_count-1) * map_len + i];
		for (int j = height_count; j != map_len-height_count; ++j) {
			height_map_[j * map_len + i] = val;
			height_map_[j * map_len + (map_len-i-1)] = val;
		}
	}
	for (int i = height_count; i != map_len-height_count; ++i)
		for (int j = width_count; j != map_len-width_count; ++j)
			height_map_[i * map_len + j] = max_fill;
}

Vector3d BumpBrickTexture::evaluate(IntersectionInfo &surface) const
{
	Vector3d u, v, w(surface.normal());
	if (std::fabs(w.x_) > 0.1)
		u = normalize(cross(Vector3d(0, 1, 0), w));
	else
		u = normalize(cross(Vector3d(1, 0, 0), w));
	v = normalize(cross(w, u));

	double ss = surface.uv().x_ / width_;
	double tt = surface.uv().y_ / height_;

	if (std::fmod(tt * 0.5, 1.0) > 0.5)
		ss += 0.5;

	double sbrick = std::floor(ss);
	double tbrick = std::floor(tt);

	ss -= sbrick;
	tt -= tbrick;

	double w = step(wf_, ss) - step(1 - wf_, ss);
	double h = step(hf_, tt) - step(1 - hf_, tt);
	double interval = w * h;
	// if (interval == 0.0) {
	// 	int i = ss * (map_len - 1);
	// 	int j = tt * (map_len - 1);
	// 	int l = (i > 0) ? (i - 1) : i;
	// 	int r = (i < (map_len-1)) ? (i + 1) : i;
	// 	int du = height_map_[j * map_len + l] - height_map_[j * map_len + r];
	// 	int u = (j > 0) ? (j - 1) : j;
	// 	int d = (j < (map_len-1)) ? (j + 1) : j;
	// 	int dv = height_map_[u * map_len + i] - height_map_[d * map_len + i];
	// }

	return mix(color1_, color2_, interval);
}

} // namespace Giraffe
