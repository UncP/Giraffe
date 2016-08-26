/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-19 01:44:58
**/

#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <ctime>
#include <random>

#include "../math/constant.hpp"
#include "../math/point.hpp"
#include "../math/vector.hpp"

class Noise
{
	public:

		constexpr static int PerlinNumber = 256;
		constexpr static int Mask = PerlinNumber - 1;

		Noise();

		double evaluate(const Point3d &) const;

		double grad(int, int, int, double, double, double) const;

	private:
		int permutationTable_[2 * PerlinNumber];
};

class Texture
{
	public:
		Texture():refl_(kDiffuse), emission_(Vector3d()) { }

		Texture(REFL refl, const Vector3d &emission):refl_(refl), emission_(emission) { }

		virtual Vector3d evaluate(const Point3d &) const = 0;

		REFL refl() const { return refl_; }
		const Vector3d& emission() const { return emission_; }

		virtual ~Texture() { }

	protected:
		REFL      refl_;
		Vector3d  emission_;
};

class ConstantTexture : public Texture
{
	public:
		ConstantTexture(const Vector3d &color, const Vector3d &emission = Vector3d(),
										const REFL refl = kDiffuse):Texture(refl, emission), color_(color) { }

		Vector3d evaluate(const Point3d &) const override { return color_; }

	private:
		Vector3d color_;
};

class StripeTexture : public Texture
{
	public:
		StripeTexture(const Vector3d &color1, const Vector3d &color2, const int axis,
			const double factor = 1.0)
		:color1_(color1), color2_(color2), axis_(axis), factor_(1.0 / factor) { }

		Vector3d evaluate(const Point3d &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		int      axis_;
		double 	 factor_;
};

class NoiseTexture : public Texture
{
	public:
		NoiseTexture(const Vector3d &color1, const Vector3d &color2, double frequency = 0.1)
		:color1_(color1), color2_(color2), frequency_(frequency) { }

		Vector3d evaluate(const Point3d &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		double   frequency_;
};

#endif /* _TEXTURE_HPP_ */