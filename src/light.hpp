/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-21 14:10:27
**/

#ifndef _LIGHT_H_
#define _LIGHT_H_

const double PI = 3.141592653589793238;

#include "vector.hpp"

class Light
{
	public:
		virtual double illuminate(const Vec3 &, Vec3 &) const = 0;

		virtual ~Light() { }
};

class PointLight : public Light
{
	public:
		PointLight(const Vec3 &origin, const double intensity = 1.0)
		:origin_(origin), intensity_(intensity) { }

		double illuminate(const Vec3 &pos, Vec3 &dir) const override {
			dir = origin_ - pos;
			double r2 = dir.length() / (4 * PI);
			if (r2 < 1.0) r2 = 1.0;
			normalize(dir);
			return intensity_ / r2;
		}

		~PointLight() { }
	private:
		Vec3 	 origin_;
		double intensity_;
};

class DirectionalLight : public Light
{
	public:
		DirectionalLight(const Vec3 &direction, const double intensity = 1.0)
		:direction_(direction), intensity_(intensity) { normalize(direction_); }

		double illuminate(const Vec3 &pos, Vec3 &dir) const override {
			dir = -direction_;
			return intensity_;
		}

		~DirectionalLight() { }
	private:
		Vec3 	 direction_;
		double intensity_;
};

#endif /* _LIGHT_H_ */