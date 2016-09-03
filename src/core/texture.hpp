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
#include "../math/vertex.hpp"

class Noise
{
	public:

		constexpr static int PerlinNumber = 256;
		constexpr static int Mask = PerlinNumber - 1;

		Noise();

		int index(int, int, int) const;

		double gnoise(const Point3d &) const;

		double turbulence(const Point3d &) const;

		double fractalSum(const Point3d &) const;

		double glattice(int, int, int, double, double, double) const;

	private:
		int     octaves_;
		int     permutationTable_[2 * PerlinNumber];
		double  gradientTable_[3 * PerlinNumber];
};

class Texture
{
	public:
		Texture():refl_(kDiffuse), emission_(Vector3d()) { }

		Texture(REFL refl, const Vector3d &emission):refl_(refl), emission_(emission) { }

		virtual Vector3d evaluate(const Vertex &) const = 0;

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

		Vector3d evaluate(const Vertex &) const override { return color_; }

	private:
		Vector3d color_;
};

class StripeTexture : public Texture
{
	public:
		StripeTexture(const Vector3d &color1, const Vector3d &color2, int axis,
									const double &factor = 1.0)
		:color1_(color1), color2_(color2), axis_(axis), factor_(1.0 / factor) { }

		Vector3d evaluate(const Vertex &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		int      axis_;
		double 	 factor_;
};

class NoiseTexture : public Texture
{
	public:
		NoiseTexture(const Vector3d &color1, const Vector3d &color2, const double &frequency = 0.1)
		:color1_(color1), color2_(color2), frequency_(frequency) { }

		Vector3d evaluate(const Vertex &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		double   frequency_;
};

class MarbleTexture : public Texture
{
	public:
		MarbleTexture(const Vector3d &color1, const Vector3d &color2, const Vector3d &color3,
									double frequency = 0.1)
		:color1_(color1), color2_(color2), color3_(color3), frequency_(frequency) { }

	Vector3d evaluate(const Vertex &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		Vector3d color3_;
		double   frequency_;
};

class BrickTexture : public Texture
{
	public:
		BrickTexture(	const Vector3d &color1, const Vector3d &color2, double width, double height,
									double interval)
		:color1_(color1), color2_(color2) {
		 	bmwidth_ = width + interval;
		 	bmheight_ = height + interval;
		 	mwf_ = (interval * 0.5) / width;
		 	mhf_ = (interval * 0.5) / height;
		 }

		Vector3d evaluate(const Vertex &) const override;

	private:
		Vector3d color1_;
		Vector3d color2_;
		double   bmwidth_;
		double 	 bmheight_;
		double   mwf_;
		double   mhf_;
};

#endif /* _TEXTURE_HPP_ */