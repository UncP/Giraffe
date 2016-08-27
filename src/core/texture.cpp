/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-19 01:57:06
**/

#include "texture.hpp"

static Noise noise;

Noise::Noise()
{
	for (int i = 0; i != PerlinNumber; ++i)
		permutationTable_[i] = i;

	std::default_random_engine generator(time(0));
	std::uniform_int_distribution<int> distribution(0, PerlinNumber-1);
	for (int i = 0; i != PerlinNumber; ++i) {
		int j = distribution(generator);
		std::swap(permutationTable_[i], permutationTable_[j]);
		permutationTable_[i + PerlinNumber] = permutationTable_[i];
	}

	octaves_ = 3;
}

double Noise::grad(int x, int y, int z, double dx, double dy, double dz) const
{
	int h = permutationTable_[permutationTable_[permutationTable_[x] + y] + z];
	h &= 15;
	double u = (h < 8 || h == 10 || h == 13) ? dx : dy;
	double v = (h >= 8 || h == 2 || h == 5) ? dy : dz;
	return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

inline double smoothStep(double t)
{
	return t * t * (3 - 2 * t);
}

inline double lerp(double x, double y, double t)
{
	return t * x + (1 - t) * y;
}

double Noise::noise(const Point3d &p) const
{
	int ix = std::floor(p.x_), iy = std::floor(p.y_), iz = std::floor(p.z_);
	double dx = p.x_ - ix, dy = p.y_ - iy, dz = p.z_ - iz;

	ix &= Mask;
	iy &= Mask;
	iz &= Mask;

	double v000 = grad(ix,   iy,   iz,   dx,   dy,   dz);
	double v100 = grad(ix+1, iy,   iz,   dx-1, dy,   dz);
	double v010 = grad(ix,   iy+1, iz,   dx,   dy-1, dz);
	double v001 = grad(ix,   iy,   iz+1, dx,   dy,   dz-1);

	double v110 = grad(ix+1, iy+1, iz,   dx-1, dy-1, dz);
	double v101 = grad(ix+1, iy,   iz+1, dx-1, dy,   dz-1);
	double v011 = grad(ix,   iy+1, iz+1, dx,   dy-1, dz-1);
	double v111 = grad(ix+1, iy+1, iz+1, dx-1, dy-1, dz-1);

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
		res += std::fabs(noise(p * f)) * a;
		f *= 2.0;
		a *= 0.5;
	}
	return res;
}

Vector3d StripeTexture::evaluate(const Point3d &sample) const {
	double var = axis_ == Xaxis ? sample.x_ : (axis_ == Yaxis ? sample.y_ : sample.z_);
	double t = (1.0 + std::sin((var * PI) * factor_)) * 0.5;
	return  t * color1_ + (1.0 - t) * color2_;
}

Vector3d NoiseTexture::evaluate(const Point3d &p) const
{
	double t = noise.noise(p * frequency_);
	if (t < 0) t = 0;
	if (t > 1) t = 1;
	return t * color1_ + (1 - t) * color2_;
}

Vector3d MarbleTexture::evaluate(const Point3d &p) const
{
	double t = noise.turbulence(p * frequency_);
	t = std::fabs(std::sin(t + p.z_ * frequency_)) * 2;

	if (t < 1) return color2_ * t + (1 - t) * color3_;
	t -= 1;
	return color1_ * t + (1 - t) * color2_;
}

Vector3d WoodTexture::evaluate(const Point3d &p) const
{
	double t = noise.noise(p * frequency_) * 10;
	if (t < 0) t = 0;
	if (t > 1) t = 1;
	return color_ * (t - std::floor(t));
}
