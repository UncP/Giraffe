/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-09-15 11:26:17
**/

#include "cube.hpp"
#include "triangle.hpp"

namespace Giraffe {

std::array<std::array<int, 4>, 6> Cube::indexes_ = {0, 1, 2, 3,
																										3, 2, 6, 7,
																										7, 6, 5, 4,
																										4, 5, 1, 0,
																										1, 5, 6, 2,
																										4, 0, 7, 3};

Cube::Cube(const Point3d &center, int length, int width, int height,
	const std::shared_ptr<Texture> &texture, const Matrix &matrix)
:texture_(texture), aabb_(new AABB())
{
	assert(aabb_);
	/*
		5	-------------- 6
		 /|           /|
		/ |          / |
	 /  |       2 /  |
 1 --------------  |
	 |  | 4       |  |
	 |  ----------|--/ 7
	 |  /         | /
	 | /          |/
	 --------------
	 0             3
	*/

	vertices_.resize(8);
	normals_. resize(6);

	length /= 2;
	width  /= 2;
	height /= 2;

	vertices_[0] = center + matrix(Vector3d(-length, -height, width));
	vertices_[1] = center + matrix(Vector3d(-length,  height, width));
	vertices_[2] = center + matrix(Vector3d( length,  height, width));
	vertices_[3] = center + matrix(Vector3d( length, -height, width));

	vertices_[4] = center + matrix(Vector3d(-length, -height, -width));
	vertices_[5] = center + matrix(Vector3d(-length,  height, -width));
	vertices_[6] = center + matrix(Vector3d( length,  height, -width));
	vertices_[7] = center + matrix(Vector3d( length, -height, -width));

	computeNormals();

	computeBounds();
}

void Cube::computeNormals()
{
	normals_[0] = normalize(cross(vertices_[0]-vertices_[1], vertices_[2]-vertices_[1]));
	normals_[1] = normalize(cross(vertices_[3]-vertices_[2], vertices_[6]-vertices_[2]));
	normals_[2] = -normals_[0];
	normals_[3] = -normals_[1];
	normals_[4] = normalize(cross(vertices_[1]-vertices_[5], vertices_[6]-vertices_[5]));
	normals_[5] = -normals_[4];
}

void Cube::computeBounds()
{
	for (int i = 0; i != 6; ++i) {
		std::array<int, 4> &idx = indexes_[i];
		for (int j = 0; j != 3; ++j) {
			double s = kInfinity, m = -kInfinity;
			for (int k = 0; k != 4; ++k) {
				if (vertices_[idx[k]][j] < s) s = vertices_[idx[k]][j];
				if (vertices_[idx[k]][j] > m) m = vertices_[idx[k]][j];
				if (vertices_[idx[k]][j] < aabb_->near(j)) aabb_->near(j) = vertices_[idx[k]][j];
				if (vertices_[idx[k]][j] > aabb_->far(j)) aabb_->far(j) = vertices_[idx[k]][j];
			}
			bounds_[i][j].first  = s;
			bounds_[i][j].second = m;
		}
	}
}

std::ostream& Cube::print(std::ostream &os) const
{
	os << "cube\nvertices\n";
	for (auto e : vertices_) os << e;
	os << "normals\n";
	for (auto e : normals_)  os << e;
	os << "bounds\n";
	for (auto each : bounds_)
		for (auto e : each)
			os << e.first << " " << e.second << std::endl;
	return os;
}

bool Cube::intersect(const Ray &ray, Isect &isect) const
{
	bool hit = false;

	if (!aabb_->intersect(ray, isect)) return hit;

	for (int i = 0; i != 6; ++i) {
		Vector3d ab(vertices_[indexes_[i][0]]-ray.origin());
		double p_to_p = dot(ab, normals_[i]);
		double dis = p_to_p / dot(ray.direction(), normals_[i]);
		if (dis < kEpsilon) continue;

		Point3d hitPos(ray.origin() + ray.direction() * dis);
		auto &bound = bounds_[i];
		bool in = true;
		for (int j = 0; j != 3; ++j) {
			double s = bound[j].first, b = bound[j].second;
			if (s != b) {
				double tmp = hitPos[j];
				if (tmp < s || tmp > b) {
					in = false;
					break;
				}
			}
		}
		if (in && dis < isect.distance()) {
			Point2d uv;
			for (int j = 0, k = 0; j != 3 && k != 2; ++j) {
				double s = bound[j].first, b = bound[j].second;
				if (s != b)
					uv[k++] = (hitPos[j] - s) / (b - s);
			}
			isect.update(dis, IntersectionInfo(hitPos, uv, normals_[i]), texture_.get());
			hit = true;
		}
	}
	return hit;
}

} // namespace Giraffe
