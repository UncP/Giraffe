/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-19 01:57:06
**/

#include "texture.hpp"

namespace Giraffe {

inline double step(double a, double x)
{
	return x >= a;
}

inline Vector3d mix(const Vector3d &a, const Vector3d &b, double t)
{
	return a * t + (1 - t) * b;
}

inline double clamp(double x, double a, double b)
{
	if (x < a) return a;
	if (x > b) return b;
	return x;
}

static Noise noise;

Noise::Noise()
{
	for (int i = 0; i != PerlinNumber; ++i)
		permutationTable_[i] = i;

	std::default_random_engine generator(time(0));
	std::uniform_int_distribution<int> distribution1(0, PerlinNumber-1);
	for (int i = 0; i != PerlinNumber; ++i) {
		int j = distribution1(generator);
		std::swap(permutationTable_[i], permutationTable_[j]);
		permutationTable_[i + PerlinNumber] = permutationTable_[i];
	}

	std::uniform_real_distribution<double> distribution2(0, 1);
	for (int i = 0; i != 3 * PerlinNumber; i += 3) {
		double j = 1 - 2 * distribution2(generator);
		double r = std::sqrt(1 - j * j);
		double theta = 2 * PI * distribution2(generator);
		gradientTable_[i]   = r * std::cos(theta);
		gradientTable_[i+1] = r * std::sin(theta);
		gradientTable_[i+2] = j;
	}

	octaves_ = 3;
}

int Noise::index(int x, int y, int z) const
{
	return permutationTable_[permutationTable_[permutationTable_[x] + y] + z];
}

double Noise::glattice(int x, int y, int z, double dx, double dy, double dz) const
{
	const double *g = &gradientTable_[index(x, y, z) * 3];
	return g[0] * dx + g[1] * dy + g[2] * dz;
}

inline double smoothStep(double t)
{
	return t * t * (3 - 2 * t);
}

inline double lerp(double x, double y, double t)
{
	return t * x + (1 - t) * y;
}

double Noise::gnoise(const Point3d &p) const
{
	int ix = std::floor(p.x_), iy = std::floor(p.y_), iz = std::floor(p.z_);
	double dx = p.x_ - ix, dy = p.y_ - iy, dz = p.z_ - iz;

	ix &= Mask;
	iy &= Mask;
	iz &= Mask;

	double v000 = glattice(ix,   iy,   iz,   dx,   dy,   dz);
	double v100 = glattice(ix+1, iy,   iz,   dx-1, dy,   dz);
	double v010 = glattice(ix,   iy+1, iz,   dx,   dy-1, dz);
	double v001 = glattice(ix,   iy,   iz+1, dx,   dy,   dz-1);

	double v110 = glattice(ix+1, iy+1, iz,   dx-1, dy-1, dz);
	double v101 = glattice(ix+1, iy,   iz+1, dx-1, dy,   dz-1);
	double v011 = glattice(ix,   iy+1, iz+1, dx,   dy-1, dz-1);
	double v111 = glattice(ix+1, iy+1, iz+1, dx-1, dy-1, dz-1);

	double wx = smoothStep(dx), wy = smoothStep(dy), wz = smoothStep(dz);

	double v00 = lerp(v000, v100, wx);
	double v01 = lerp(v010, v001, wx);
	double v10 = lerp(v110, v101, wx);
	double v11 = lerp(v011, v111, wx);

	double v0 = lerp(v00, v01, wy);
	double v1 = lerp(v10, v11, wy);

	return lerp(v0, v1, wz);
}

double Noise::turbulence(const Point3d &p) const
{
	double res = 0;
	double f = 1, a = 1;
	for (int i = 0; i != octaves_; ++i) {
		res += std::fabs(gnoise(p * f)) * a;
		f *= 2.0;
		a *= 0.5;
	}
	return res;
}

double Noise::fractalSum(const Point3d &p) const
{
	double res = 0;
	double f = 1, a = 1;
	for (int i = 0; i != octaves_; ++i) {
		res += (2 * gnoise(p * f) - 1) * a;
		f *= 2.0;
		a *= 0.5;
	}
	return res;
}

Vector3d StripeTexture::evaluate(Vertex &v) const
{
	double var = axis_ == Xaxis ? v.position().x_ :
																(axis_ == Yaxis ? v.position().y_ : v.position().z_);

	double t = (1.0 + std::sin((var * PI) * factor_)) * 0.5;
	return mix(color1_, color2_, t);
}

Vector3d NoiseTexture::evaluate(Vertex &v) const
{
	double t = noise.gnoise(v.position() * frequency_);
	if (t < 0) t = 0;
	if (t > 1) t = 1;
	return mix(color1_, color2_, t);
}

Vector3d MarbleTexture::evaluate(Vertex &v) const
{
	double t = noise.fractalSum(v.position() * frequency_);
	double tt = 2 * std::fabs(std::sin(v.position().z_ * frequency_ + t));

	if (tt < 1)
		return color2_ * tt + (1 - tt) * color3_;
	tt -= 1;
	return color1_ * tt + (1 - tt) * color2_;
}

Vector3d BrickTexture::evaluate(Vertex &v) const
{
	double ss = v.uv().x_ / width_;
	double tt = v.uv().y_ / height_;

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

Vector3d ImageTexture::evaluate(Vertex &v) const
{
	int uu = static_cast<int>(std::fmod(v.uv().x_ * frequency_, 1.0) * (width_ - 1));
	int vv = static_cast<int>(std::fmod(v.uv().y_ * frequency_, 1.0) * (height_ - 1));
	return image_[uu + vv * width_];
}

void BumpBrickTexture::generateHeightMap()
{
	int width_count  = static_cast<int>(static_cast<double>(map_len) * wf_ + 0.5);
	int height_count = static_cast<int>(static_cast<double>(map_len) * hf_ + 0.5);
	// std::cout << width_count << " " << height_count << std::endl;
	int max_blank = std::max(width_count, height_count);
	int max_fill  = max_blank + 1;



	for (int i = width_count; i != map_len - width_count; ++i)
		for (int j = height_count; j != map_len - height_count; ++j)
			height_map_[i * map_len + j] = max_fill;
	bool flag = true;
	for (int i = 0; i != map_len; ++i) {
		for (int j = 0; j != map_len; ++j) {
			if((i <= 20 && (j <=20 || j >= 80)) || (i >= 80 && (j <= 20 || j >= 80))) {
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

Vector3d BumpBrickTexture::evaluate(Vertex &v) const
{
	double ss = v.uv().x_ / width_;
	double tt = v.uv().y_ / height_;

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

} // namespace Giraffe
