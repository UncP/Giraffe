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

#include "utility.hpp"

class Light
{
	public:
		Light(const Vec3 &color, const double intensity):color_(color), intensity_(intensity) { }

		virtual void illuminate(const Vec3 &, Vec3 &, Vec3 &, double &dis) const = 0;

		virtual ~Light() { }

		Vec3 color_;
		double intensity_;
};

class PointLight : public Light
{
	public:
		PointLight(	const Vec3 	&origin,
								const double intensity = 1.0,
								const Vec3 	&color 		 = Vec3(1.0, 1.0, 1.0))
		:Light(color, intensity), origin_(origin) { }

		void illuminate(const Vec3 &pos, Vec3 &dir, Vec3 &intensity, double &dis) const override {
			dir = origin_ - pos;
			dis = dir.length();
			double r2 = dis / (4 * PI);
			normalize(dir);
			intensity = color_ * (intensity_ / r2);
		}

		~PointLight() { }
	private:
		Vec3 	 origin_;
};

class DirectionalLight : public Light
{
	public:
		DirectionalLight(	const Vec3 	&direction,
											const double intensity = 1.0,
											const Vec3 	&color 		 = Vec3(1.0, 1.0, 1.0))
		:Light(color, intensity), direction_(direction) { normalize(direction_); }

		void illuminate(const Vec3 &pos, Vec3 &dir, Vec3 &intensity, double &dis) const override {
			dir = -direction_;
			intensity = color_ * intensity_;
		}

		~DirectionalLight() { }
	private:
		Vec3 	 direction_;
};

class EnvironmentalLight : public Light
{
	public:
		EnvironmentalLight(	const double intensity = 1.0,
												const Vec3 	&color 		 = Vec3(1.0, 1.0, 1.0)):Light(color, intensity) { }

		void illuminate(const Vec3 &pos, Vec3 &dir, Vec3 &intensity, double &dis) const override {
			intensity = color_ * intensity_;
		}

		~EnvironmentalLight() { }
};

#endif /* _LIGHT_H_ */