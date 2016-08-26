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

double Noise::evaluate(const Point3d &p) const
{
	int ix = std::floor(p.x_), iy = std::floor(p.y_), iz = std::floor(p.z_);
	double dx = p.x_ - ix, dy = p.y_ - iy, dz = p.z_ - iz;

	ix &= Mask;
	iy &= Mask;
	iz &= Mask;

	double v000 = grad(ix, iy, iz, dx, dy, dz);
	double v100 = grad(ix+1, iy, iz, dx-1, dy, dz);
	double v010 = grad(ix, iy+1, iz, dx, dy-1, dz);
	double v001 = grad(ix, iy, iz+1, dx, dy, dz-1);

	double v110 = grad(ix+1, iy+1, iz, dx-1, dy-1, dz);
	double v101 = grad(ix+1, iy, iz+1, dx-1, dy, dz-1);
	double v011 = grad(ix, iy+1, iz+1, dx, dy-1, dz-1);
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

Vector3d StripeTexture::evaluate(const Point3d &sample) const {
	double var = axis_ == Xaxis ? sample.x_ : sample.y_;
	double t = (1.0 + std::sin((var * PI) * factor_)) * 0.5;
	return  t * color1_ + (1.0 - t) * color2_;
}

Vector3d NoiseTexture::evaluate(const Point3d &p) const
{
	double n = noise.evaluate(p * frequency_);
	// if (n > 1) return color1_ * (n - 1);
	// if (n < 0) return color2_ * (1 + n);
	if (n <= 0.5) return color1_;
	return color2_;
	// return n * color1_ + (1 - n) * color2_;
}
