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

Material::Material(Type type, const Texture *texture, double roughness, int pow)
:type_(type), texture_(texture), sin_(std::sin(radian(roughness))),
 cos_(std::cos(radian(roughness))), pow_(pow) { }

Color Material::brdf(const Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const
{
	switch (type_) {
		case kDiffuse:
			return sampleDiffuse(isect, out, in, pdf);
		case kReflect:
			return sampleReflect(isect, out, in, pdf);
		case kRefract:
			return sampleRefract(isect, out, in, pdf);
		case kPhong:
			return samplePhong(isect, out, in, pdf);
		case kGlossy:
			return sampleGlossy(isect, out, in, pdf);
		case kRetro:
			return sampleRetro(isect, out, in,  pdf);
		case kHalton:
			return sampleHalton(isect, out, in,  pdf);
	}
	assert(0);
}

Color Material::evaluate(const Vector3d &out, const Vector3d &in, const Isect &isect) const
{
	if (type_ == kPhong) {
		Vector3d mid(normalize(in - out));
		return texture_->evaluate(isect.vertex()) * dot(isect.normal(), in) +
					 Vector3d(1.5) * std::pow(dot(isect.normal(), mid), pow_);
	} else {
		Vector3d color = texture_->evaluate(isect.vertex());
		return color * dot(isect.normal(), in);
	}
}

Color Material::sampleDiffuse(const Isect &isect, const Vector3d &out, Vector3d &in, double &pdf)
const
{
	in = sampleCosHemisphere(isect.normal());
	return texture_->evaluate(isect.vertex());
}

Color Material::sampleReflect(const Isect &isect, const Vector3d &out, Vector3d &in, double &pdf)
const
{
	in = normalize(out - (2 * dot(out, isect.normal())) * isect.normal());

	return texture_->evaluate(isect.vertex());
}

Color Material::sampleRefract(const Isect &isect, const Vector3d &out, Vector3d &in, double &pdf)
const
{
	return Vector3d();
}

Color Material::samplePhong(const Isect &isect, const Vector3d &out, Vector3d &in, double &pdf)
const
{
	in = sampleCosHemisphere(isect.normal());
	return texture_->evaluate(isect.vertex());
}

Color Material::sampleGlossy(const Isect &isect, const Vector3d &out, Vector3d &in, double &pdf)
const
{
	in = sampleCosSphere(
		normalize(out - (2 * dot(out, isect.normal())) * isect.normal()), sin_, cos_);

	return texture_->evaluate(isect.vertex());
}

Color Material::sampleRetro(const Isect &isect, const Vector3d &out, Vector3d &in, double &pdf)
const
{
	in = sampleCosSphere(-out, sin_, cos_);

	return texture_->evaluate(isect.vertex());
}

Color Material::sampleHalton(const Isect &isect, const Vector3d &out, Vector3d &in, double &pdf)
const
{
	return Vector3d();
}

} // namespace Giraffe
