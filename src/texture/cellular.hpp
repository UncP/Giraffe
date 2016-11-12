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
		CellularTexture(const std::vector<Vector3d> &colors)
		:colors_(colors), n_close_(colors_.size()) { }

		Vector3d evaluate(Vertex &vertex) const override;

	private:
		static int PoissonCount[256];

		class Neighbor {
			public:
				Neighbor():distance_(kInfinity) { }

				bool operator<(const Neighbor &that) { return distance_ < that.distance_; }

				double       distance_;
				Point3d      position_;
				unsigned int id_;
		};

		void addSample(const Point3<unsigned long> &upos, const Point3d &fpos,
			std::vector<Neighbor> &neighbors) const;

		std::vector<Vector3d> colors_;
		int n_close_;
};

} // namespace Giraffe

#endif /* _CELLULAR_TEXTURE_HPP_ */