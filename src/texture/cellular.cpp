/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-10 20:23:14
**/

#include "cellular.hpp"

namespace Giraffe {

int CellularTexture::PoissonCount[256] = {
4,3,1,1,1,2,4,2,2,2,5,1,0,2,1,2,2,0,4,3,2,1,2,1,3,2,2,4,2,2,5,1,2,3,
2,2,2,2,2,3,2,4,2,5,3,2,2,2,5,3,3,5,2,1,3,3,4,4,2,3,0,4,2,2,2,1,3,2,
2,2,3,3,3,1,2,0,2,1,1,2,2,2,2,5,3,2,3,2,3,2,2,1,0,2,1,1,2,1,2,2,1,3,
4,2,2,2,5,4,2,4,2,2,5,4,3,2,2,5,4,3,3,3,5,2,2,2,2,2,3,1,1,4,2,1,3,3,
4,3,2,4,3,3,3,4,5,1,4,2,4,3,1,2,3,5,3,2,1,3,1,3,3,3,2,3,1,5,5,4,2,2,
4,1,3,4,1,5,3,3,5,3,4,3,2,2,1,1,1,1,1,2,4,5,4,5,4,2,1,5,1,1,2,3,3,3,
2,5,2,3,3,2,0,2,1,1,4,2,1,3,2,1,2,2,3,2,5,5,3,4,5,5,2,4,4,5,3,2,2,2,
1,4,2,3,3,4,2,5,4,2,4,2,2,2,4,5,3,2};

Vector3d CellularTexture::evaluate(Vertex &vertex) const
{
	const Point3d &fpos = vertex.position();
	const Point3<unsigned long> upos(	(unsigned long)std::floor(fpos.x_),
																		(unsigned long)std::floor(fpos.y_),
																		(unsigned long)std::floor(fpos.z_));
	std::vector<Neighbor> neighbors(n_close_, Neighbor());

	addSample(upos, fpos, neighbors);

	return Vector3d();
}

void CellularTexture::addSample(const Point3<unsigned long> &upos, const Point3d &fpos,
	std::vector<Neighbor> &neighbors) const
{
	double dx, dy, dz, fx, fy, fz, d2;
	int count, i, j, index;
	unsigned long seed, this_id;

	seed = 702395077 * upos.x_ + 915488749 * upos.y_ + 2120969693 * upos.z_;

	count = PoissonCount[seed >> 24];
	seed = 1402024253 * seed + 586950981;
	for (j=0; j<count; j++)
	{
		this_id = seed;
		seed = 1402024253 * seed + 586950981;
		fx = (seed+0.5) * (1.0/4294967296.0);
		seed = 1402024253 * seed + 586950981;
		fy = (seed+0.5) * (1.0/4294967296.0);
		seed = 1402024253 * seed + 586950981;
		fz= (seed+0.5) * (1.0/4294967296.0);
		seed = 1402024253 * seed + 586950981;

		dx = upos.x_ + fx - fpos.x_;
		dy = upos.y_ + fy - fpos.y_;
		dz = upos.z_ + fz - fpos.z_;
}

} // namespace Giraffe
