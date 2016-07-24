/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-07-23 12:02:46
**/

#include "utility.hpp"

double cos_[360];

double sin_[360];

void initLookupTable()
{
	for (int i = 0; i < 360; ++i) {
		cos_[i] = cos(static_cast<double>(i) * (PI / 180.0));
		sin_[i] = sin(static_cast<double>(i) * (PI / 180.0));
	}
}

double Cos(int angle) { return cos_[(angle % 360)]; }

double Sin(int angle) { return sin_[(angle % 360)]; }

static const double kRefractionRatio = 1.3;

void reflect(	const Vec3 &dir,
							const Vec3 &normal,
							Vec3 &refl)
{
	refl = dir - 2 * dot(dir, normal) * normal;
	normalize(refl);
}

void fresnel(	const Vec3 &dir,
							const Vec3 &normal,
							const bool &into,
							Vec3 &refrDir,
							double &kr)
{
	double etai = 1.0, etat = kRefractionRatio;
	double ior;
	if (into) {
		ior = 1.0 / kRefractionRatio;
		std::swap(etai, etat);
	} else {
		ior = kRefractionRatio;
	}
	double cos1 = -dot(dir, normal);
	double sin2 = ior * ior * (1.0 - cos1 * cos1);
	if (sin2 > 1.0) {
		kr = 0.0;
	}
	else {
		double cos2 = std::sqrt(1 - sin2);
		refrDir = dir * ior + normal * (ior * cos1 - cos2);
		normalize(refrDir);
		double Rs = ((etat * cos1) - (etai * cos2)) / ((etat * cos1) + (etai * cos2));
		double Rp = ((etai * cos1) - (etat * cos2)) / ((etai * cos1) + (etat * cos2));
		kr = (Rs * Rs + Rp * Rp) / 2;
	}
}

void createWorldCoordinate(const Vec3 &N, Vec3 &X, Vec3 &Y)
{
	if (std::abs(N.x_) > std::abs(N.y_))
		X = Vec3(N.z_, 0, -N.x_);
	else
		X = Vec3(0, -N.z_, N.y_);
	normalize(X);
	Y = cross(N, X);
	normalize(Y);
}

Vec3 uniformHemiSphere(const double &a, const double &b)
{
	double sini = sqrt(1 - a * a);
	double cosi = 2 * PI * b;
	double x = sini * cos(cosi);
	double z = sini * sin(cosi);
	return Vec3(x, a, z);
}
