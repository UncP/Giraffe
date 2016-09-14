/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-05 16:16:15
**/

#include "mesh.hpp"

#define  NEXT(i) ((i+1)%3)
#define  PREV(i) ((i+2)%3)

enum ObjFormat { None, VERTEX_ONLY, VERTEX_UV, VERTEX_NORMAL, VERTEX_UV_NORMAL };

std::ostream& Mesh::print(std::ostream & os) const
{
	os << "edge size: " << edges_.size() << std::endl;
	for (auto &each : edges_) {
		os << each;
	}
	return os;
}

void Mesh::load()
{
	std::ifstream in(std::string("../models/" + name_ + ".obj").c_str());
	if (!in.is_open()) {
		std::cerr << "loading mesh failed :(\n" << std::endl;
		exit(-1);
	}

	std::vector<Vector3f> normal;
	ObjFormat format = None;

	std::string buf, token;
	uint32_t lineNum = 0;
	while (getline(in, buf)) {
		std::istringstream line(buf);
		line >> token;
		++lineNum;

		if (token == "v") {
			Point3f v;
			line >> v.x_ >> v.y_ >> v.z_;
			if (line.fail()) {
				std::cerr << "postion syntax error in line " << lineNum << std::endl;
				exit(-1);
			}
			vertexes_.push_back(new MeshVertex(v));
		} else if (token == "vn") {
			Vector3f n;
			line >> n.x_ >> n.y_ >> n.z_;
			if (line.fail()) {
				std::cerr << "normal syntax error in line " << lineNum << std::endl;
				exit(-1);
			}
			normal.push_back(n);
		} else if (token == "f") {
			std::vector<std::string> face_tokens;
			while (true) {
				std::string s;
				line >> s;
				if (line.fail()) break;
				face_tokens.push_back(s);
			}

			if (!format) {
				token = face_tokens[0];
				if (token.find("//") != std::string::npos) {
					format = VERTEX_NORMAL;
				} else {
					std::cerr << "face type not supported :(\n";
					exit(-1);
				}
			}

			if (face_tokens.size() != 3) {
				std::cerr << "face syntax error in line " << lineNum << std::endl;
				exit(-1);
			}

			int p[3] = {0, 0, 0};
			int n[3] = {0, 0, 0};
			for (size_t i = 0; i != 3; ++i) {
				switch (format) {
					case VERTEX_NORMAL:
						sscanf(face_tokens[i].c_str(), "%d//%d", &p[i], &n[i]);
						break;
					default:
						std::cerr << "face type not supported :(\n";
						exit(-1);
						break;
				}
				--p[i], --n[i];
			}
			if (n[0] != n[1] || n[0] != n[2]) {
				std::cerr << "invalid normal index in face :(\n";
				exit(-1);
			}
			MeshTriangle *triangle = new MeshTriangle(normal[n[0]]);
			triangles_.push_back(triangle);
			for (size_t i = 0; i != 3; ++i) {
				MeshVertex *h = vertexes_[p[i]], *t = vertexes_[p[(i+1)%3]];
				if (h < t) std::swap(h, t);
				MeshEdge edge(h, t);
				auto iter = edges_.find(edge);
				if (iter == edges_.end()) {
					edges_.insert(edge);
					edge.setFace(triangle);
				} else {
					edge = *iter;
					edge.setFace(triangle);
				}
				if (!i) triangle->setEdge(&edge);
			}
		}
		line.clear();
		token.clear();
	}
	assert((3 * triangles_.size()) == (2 * edges_.size()));
}

/*
void Mesh::computeBox(std::vector<double> &near, std::vector<double> &far,
	const Vector3f *normal) const
{
	for (size_t i = 0, iEnd = near.size(); i != iEnd; ++i)
		for (size_t j = 0, jEnd = vertexes_.size(); j != jEnd; ++j) {
			double dis = proj(vertexes_[j].pos(), normal[i]);
			if (dis < near[i]) near[i] = dis;
			if (dis > far[i]) far[i] = dis;
		}
}
*/

bool Mesh::intersect(const Ray &ray, Isect &isect) const
{
/*
	bool flag = false;
	for (size_t i = 0, end = triangles_.size(); i != end; ++i) {
		const MeshTriangle &tri = triangles_[i];
		const Point3f &a = vertexes_[tri.vex(0)].pos();
		const Point3f &b = vertexes_[tri.vex(1)].pos();
		const Point3f &c = vertexes_[tri.vex(2)].pos();

		Vector3f a_b	(a - b);
		Vector3f a_c	(a - c);
		Vector3f a_pos(a - ray.ori_);

		Vector3f a_bCross_a_pos(cross(a_b, a_pos));
		Vector3f a_cCross_dir	 (cross(a_c, ray.dir_));

		double m = 1.0 / dot(a_b, a_cCross_dir);

		double t = dot(a_c, a_bCross_a_pos) * (-m);
		if (t < kEpsilon) continue;

		double u = dot(a_pos, a_cCross_dir) * m;
		if (u < 0.0 || u > 1.0) continue;

		double v = dot(ray.dir_, a_bCross_a_pos) * m;
		if (v < 0.0 || v > (1.0 - u)) continue;

		if (t < isect.dis_) {
			Point3f hitPos(ray.ori_ + ray.dir_ * t);
			isect.update(t, this, hitPos, triangles_[i].norm(), kDiffuse, Vector3f(.5),
				false, Vector3f(1));
			flag = true;
		}
	}
	return flag;
*/
	return false;
}

void Mesh::subdivide()
{

}
