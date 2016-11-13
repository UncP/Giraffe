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
		enum Distance {kEuclidean, kManhattan, kRadialManhattan, kSuperquadratic, kBiased};

		enum Combine {kDistance, kClosest};

		CellularTexture(const Vector3d &color, int n_close,
			Distance type = kEuclidean, Combine combine = kDistance)
		:color_(color), n_close_(n_close), type_(type), combine_(kClosest) { }

		Vector3d evaluate(Vertex &vertex) const override;

	private:
		static int PoissonCount[256];

		class Neighbor {
			public:
				Neighbor():distance_(kInfinity) { }

				Neighbor(double distance, const Point3d &position, unsigned int id)
				:distance_(distance), position_(position), id_(id) { }

				bool operator<(const Neighbor &that) const { return distance_ < that.distance_; }

				double        distance_;
				Point3d       position_;
				unsigned int id_;
		};

		void addSample(const Point3i &ipos, const Point3d &fpos,
			std::vector<Neighbor> &neighbors) const;

		double distance(const Point3d &position) const;

		Vector3d combine(const std::vector<Neighbor> &neighbors) const;

		Vector3d color_;
		int      n_close_;
		Distance type_;
		Combine  combine_;
};

} // namespace Giraffe

#endif /* _CELLULAR_TEXTURE_HPP_ */