/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-29 22:38:35
**/

#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include <cassert>

#include "../math/point.hpp"
#include "../math/vector.hpp"
#include "../utility/isect.hpp"

namespace Giraffe {

class Material
{
	public:
		enum Type { kDiffuse = 1,
								kReflect = 2,
								kRefract = 4,
								kPhong   = kDiffuse | 8,
								kGlossy  = kDiffuse | 16,
								kRetro   = kDiffuse | 32,
								kHalton  = 64};

		Material(Type type, const Vector3d &color, double roughness = 0, int pow = 0)
		:type_(type), color_(color), sin_(std::sin(radian(roughness))),
		 cos_(std::cos(radian(roughness))), pow_(pow) { }

		Type type() const { return type_; }

		Color brdf(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf);

		Color evaluate(	const Vector3d &out, const Vector3d &in, const Vector3d &normal);

		virtual Color sample(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf)
		{
			return Vector3d(0);
		}

		virtual ~Material() { }

	protected:
		Type type_;

	private:
		Color sampleDiffuse(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf);
		Color sampleReflect(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf);
		Color sampleRefract(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf);
		Color samplePhong(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf);
		Color sampleGlossy(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf);
		Color sampleRetro(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf);
		Color sampleHalton(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf);

		Color evaluateDiffuse(const Vector3d &out, const Vector3d &in, const Vector3d &normal);
		Color evaluatePhong(const Vector3d &out, const Vector3d &in, const Vector3d &normal);


		Vector3d color_;
		double   sin_;
		double   cos_;
		int      pow_;
};

} // namespace Giraffe

#endif /* _MATERIAL_HPP_ */