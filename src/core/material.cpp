/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 22:38:43
**/

#include "../utility/sampler.hpp"

#include "material.hpp"

namespace Giraffe {

Material::Material(Type type, const Texture *texture, double roughness = 0, int pow = 0)
:type_(type), texture_(texture), sin_(std::sin(radian(roughness))),
 cos_(std::cos(radian(roughness))), pow_(pow) { }

Color Material::brdf(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf)
{
	switch (type_) {
		case kDiffuse:
			return sampleDiffuse(out, in, normal, pdf);
		case kReflect:
			return sampleReflect(out, in, normal, pdf);
		case kRefract:
			return sampleRefract(out, in, normal, pdf);
		case kPhong:
			return samplePhong(out, in, normal, pdf);
		case kGlossy:
			return sampleGlossy(out, in, normal, pdf);
		case kRetro:
			return sampleRetro(out, in, normal, pdf);
		case kHalton:
			return sampleHalton(out, in, normal, pdf);
	}
	assert(0);
}

Color Material::evaluate(const Vector3d &out, const Vector3d &in,
	const Point3d &position, const Point2d &uv, Vector3d &normal)
{
	if (type_ == kPhong) {
		Vector3d mid(normalize(in - out));
		return texture_->evaluate(position, uv, normal) * dot(normal, in) +
					 Vector3d(1.5) * std::pow(dot(normal, mid), pow_);
	} else {
		Vector3d color = texture_->evaluate(position, uv, normal);
		return color * dot(normal, in);
	}
}

Color Material::sampleDiffuse(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{
	in = sampleCosHemisphere(normal);
	return color_;
}

Color Material::sampleReflect(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{
	in = normalize(out - (2 * dot(out, normal)) * normal);

	return color_;
}

Color Material::sampleRefract(const Vector3d &out, Vector3d &in, const Vector3d &Normal,
	double &pdf)
{
	return Vector3d();
}

Color Material::samplePhong(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{
	in = sampleCosHemisphere(normal);
	return color_;
}

Color Material::sampleGlossy(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{
	in = sampleCosSphere(normalize(out - (2 * dot(out, normal)) * normal), sin_, cos_);

	return color_;
}

Color Material::sampleRetro(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{
	in = sampleCosSphere(-out, sin_, cos_);

	return color_;
}

Color Material::sampleHalton(const Vector3d &out, Vector3d &in, const Vector3d &normal,
	double &pdf)
{
	return Vector3d();
}

} // namespace Giraffe
