/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-07-23 12:02:46
**/

#include "utility.hpp"

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
		double a = etat - etai, b = etat + etai;
		double R0 = (a * a) / (b *b);
		double c = 1 - (into ? cos1 : dot(refrDir, -normal));
		double Re = R0 + (1 - R0) * pow(c, 5);
		kr = 1 - Re;
		// double Rs = ((etat * cos1) - (etai * cos2)) / ((etat * cos1) + (etai * cos2));
		// double Rp = ((etai * cos1) - (etat * cos2)) / ((etai * cos1) + (etat * cos2));
		// kr = (Rs * Rs + Rp * Rp) / 2;
	}
}
