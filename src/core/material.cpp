/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 22:38:43
**/

#include "sampler.hpp"

#include "material.hpp"

namespace Giraffe {

Material::Material(Type type, const Texture *texture, double roughness, int pow)
:type_(type), texture_(texture), sin_(std::sin(radian(roughness))),
 cos_(std::cos(radian(roughness))), pow_(pow) { }

Color Material::brdf(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const
{
	Color color = texture_->evaluate(isect.vertex());
	isect.setNormal(normalize(isect.normal()));
	switch (type_) {
		case kDiffuse:
			sampleDiffuse(isect, out, in, pdf);
			break;
		case kReflect:
			sampleReflect(isect, out, in, pdf);
			break;
		case kRefract:
			sampleRefract(isect, out, in, pdf);
			break;
		case kPhong:
			samplePhong(isect, out, in, pdf);
			break;
		case kGlossy:
			sampleGlossy(isect, out, in, pdf);
			break;
		case kRetro:
			sampleRetro(isect, out, in, pdf);
			break;
		case kHalton:
			sampleHalton(isect, out, in, pdf);
			break;
		default:
			assert(0);
	}
	return color;
}

Color Material::evaluate(const Vector3d &out, const Vector3d &in, Isect &isect) const
{
	Color color = texture_->evaluate(isect.vertex());
	isect.setNormal(normalize(isect.normal()));
	if (type_ == kPhong) {
		Vector3d mid(normalize(in - out));
		return color * dot(isect.normal(), in) +
			Vector3d(1.5) * std::pow(dot(isect.normal(), mid), pow_);
	} else {
		return color * dot(isect.normal(), in);
	}
}

void Material::sampleDiffuse(Isect &isect, const Vector3d &out, Vector3d &in,double &pdf) const
{
	in = sampleCosHemisphere(isect.normal());
}

void Material::sampleReflect(Isect &isect, const Vector3d &out, Vector3d &in,double &pdf) const
{
	in = normalize(out - (2 * dot(out, isect.normal())) * isect.normal());
}

void Material::sampleRefract(Isect &isect, const Vector3d &out, Vector3d &in,
	double &pdf) const
{
}

void Material::samplePhong(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const
{
	in = sampleCosHemisphere(isect.normal());
}

void Material::sampleGlossy(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const
{
	in = sampleCosSphere(
		normalize(out - (2 * dot(out, isect.normal())) * isect.normal()), sin_, cos_);
}

void Material::sampleRetro(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const
{
	in = sampleCosSphere(-out, sin_, cos_);
}

void Material::sampleHalton(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const
{
}

} // namespace Giraffe
