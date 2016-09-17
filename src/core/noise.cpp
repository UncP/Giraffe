/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-17 16:57:31
**/

#include <ctime>
#include <random>

#include "noise.hpp"

namespace Giraffe {

const Noise& Noise::getNoise()
{
	static Noise noise;
	return noise;
}

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

} // namespace Giraffe
