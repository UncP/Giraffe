/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-10 20:22:48
**/

#ifndef _CELLULAR_TEXTURE_HPP_
#define _CELLULAR_TEXTURE_HPP_

#include <vector>

#include "../core/texture.hpp"

namespace Giraffe {

class CellularTexture : public Texture
{
	public:
		CellularTexture(const Vector3d &color1, const Vector3d &color2, int n_close)
		:color1_(color1), color2_(color2), n_close_(n_close) { }

		Vector3d evaluate(Vertex &vertex) const override;

	private:
		static int PoissonCount[256];

		class Neighbor {
			public:
				Neighbor():distance_(kInfinity) { }

				Neighbor(double distance, const Point3d &position, unsigned int id)
				:distance_(kInfinity), position_(position), id_(id) { }

				bool operator<(const Neighbor &that) { return distance_ < that.distance_; }

				double       distance_;
				Point3d      position_;
				unsigned int id_;
		};

		void addSample(const Point3i &upos, const Point3d &fpos,
			std::vector<Neighbor> &neighbors) const;

		Vector3d color1_;
		Vector3d color2_;
		int n_close_;
};

} // namespace Giraffe

#endif /* _CELLULAR_TEXTURE_HPP_ */