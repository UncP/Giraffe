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
#include "texture.hpp"

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

		Material(Type type, const Texture *texture, double roughness = 0, int pow = 0);

		Type type() const { return type_; }

		Color brdf(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const;

		Color evaluate(const Vector3d &out, const Vector3d &in, Isect &isect) const;

		virtual Color sample(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf){
			return Vector3d(0);
		}

		virtual ~Material() { }

	protected:
		Type type_;

	private:
		void sampleDiffuse(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const;
		void sampleReflect(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const;
		void sampleRefract(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const;
		void samplePhong(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const;
		void sampleGlossy(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const;
		void sampleRetro(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const;
		void sampleHalton(Isect &isect, const Vector3d &out, Vector3d &in, double &pdf) const;

		const Texture *texture_;
		double         sin_;
		double         cos_;
		int            pow_;
};

} // namespace Giraffe

#endif /* _MATERIAL_HPP_ */