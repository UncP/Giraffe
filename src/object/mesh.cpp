/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-05 16:16:15
**/

#include "mesh.hpp"

enum ObjFormat { None, VERTEX_ONLY, VERTEX_UV, VERTEX_NORMAL, VERTEX_UV_NORMAL };

std::ostream& Mesh::print(std::ostream &os) const
{
	os << "vertices\n";
	for (size_t i = 0; i != vertexes_.size(); ++i)
		os << vertexes_[i];
	os << "triangles\n";
	for (size_t i = 0; i != triangles_.size(); ++i)
		os << triangles_[i];
	return os;
}

void Mesh::_load()
{
	std::ifstream in(std::string("../models/" + name_ + ".obj").c_str());
	if (!in.is_open()) {
		std::cerr << "loading mesh failed :(\n" << std::endl;
		exit(-1);
	}

	std::vector<Vector3d> normal;
	ObjFormat format = None;

	std::string buf, token;
	uint32_t lineNum = 0;
	while (getline(in, buf)) {
		std::istringstream line(buf);
		line >> token;
		++lineNum;

		if (token == "v") {
			Point3d v;
			line >> v.x_ >> v.y_ >> v.z_;
			if (line.fail()) {
				std::cerr << "postion syntax error in line " << lineNum << std::endl;
				exit(-1);
			}
			vertexes_.push_back(Vertex(v));
		} else if (token == "vn") {
			Vector3d n;
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

			Triangle tri;
			Point3u p;
			int n[3] = {0, 0, 0}, t[3] = {0, 0, 0};
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
				--p[i], --n[i], --t[i];
			}
			if (n[0] != n[1] || n[0] != n[2]) {
				std::cerr << "invalid normal index in face :(\n";
				exit(-1);
			}
			tri.setVertex(p);
			tri.setNormal(normal[n[0]]);
			triangles_.push_back(tri);
		}
		line.clear();
		token.clear();
	}

	size_t max = vertexes_.size();
	for (size_t i = 0, end = triangles_.size(); i != end; ++i) {
		const Triangle &tri = triangles_[i];
		if (tri.vex(0) >= max || tri.vex(1) >= max || tri.vex(2) >= max) {
			std::cerr << "invalid vertice index :(\n";
			exit(-1);
		}
	}
}

void Mesh::computeBox(std::vector<double> &near, std::vector<double> &far,
	const Vector3d *normal) const
{
	for (size_t i = 0, iEnd = near.size(); i != iEnd; ++i)
		for (size_t j = 0, jEnd = vertexes_.size(); j != jEnd; ++j) {
			double dis = proj(vertexes_[j].pos(), normal[i]);
			if (dis < near[i]) near[i] = dis;
			if (dis > far[i]) far[i] = dis;
		}
}

bool Mesh::intersect(const Ray &ray, Isect &isect) const
{
	bool flag = false;
	for (size_t i = 0, end = triangles_.size(); i != end; ++i) {
		const Triangle &tri = triangles_[i];
		const Point3d &a = vertexes_[tri.vex(0)].pos();
		const Point3d &b = vertexes_[tri.vex(1)].pos();
		const Point3d &c = vertexes_[tri.vex(2)].pos();

		Vector3d a_b	(a - b);
		Vector3d a_c	(a - c);
		Vector3d a_pos(a - ray.ori_);

		Vector3d a_bCross_a_pos(cross(a_b, a_pos));
		Vector3d a_cCross_dir	 (cross(a_c, ray.dir_));

		double m = 1.0 / dot(a_b, a_cCross_dir);

		double t = dot(a_c, a_bCross_a_pos) * (-m);
		if (t < kEpsilon) continue;

		double u = dot(a_pos, a_cCross_dir) * m;
		if (u < 0.0 || u > 1.0) continue;

		double v = dot(ray.dir_, a_bCross_a_pos) * m;
		if (v < 0.0 || v > (1.0 - u)) continue;

		if (t < isect.dis_) {
			Point3d hitPos(ray.ori_ + ray.dir_ * t);
			isect.update(t, this, hitPos, triangles_[i].norm(), kDiffuse, Vector3d(.5),
				false, Vector3d(1));
			flag = true;
		}
	}
	return flag;
}

void Mesh::traverseOfVertex() const
{
	for (size_t i = 0; i != vertexes_.size(); ++i) {
		Point2i p = vertexes_[i].tri();
		std::cout << "i = " << i << std::endl;
		Point2i pp = p;
		for (;;) {
			std::cout << pp.x_ << " " << pp.y_ << std::endl;
			// pp = triangles_[p.x_].nbr(p.y_);
			int32_t index = triangles_[pp.x_].nbr(pp.y_);
			pp = Point2i(index, pp.y_);
			if (pp == p) break;
			getchar();
		}
		std::cout << std::endl;
	}
}

void Mesh::_prepare()
{
	int count = 0, total = triangles_.size() * 3 / 2;
	for (auto i = triangles_.begin(); i != triangles_.end(); ++i) {
		for (size_t m = 0; m != 3; ++m) {
			std::pair<unsigned int, unsigned int> p1(i->vex(m), i->vex((m+1)%3));
			for (auto j = i + 1; j != triangles_.end(); ++j) {
				for (size_t n = 0; n != 3; ++n) {
					std::pair<unsigned int, unsigned int> p2(j->vex((n+1)%3), j->vex(n));
					if (p1 == p2) {
						vertexes_[i->vex(m)].setTriangle(std::distance(triangles_.begin(), i), m);
						i->setNeighbor(std::distance(triangles_.begin(), j), m);
						j->setNeighbor(std::distance(triangles_.begin(), i), n);
						if (++count == total) goto end;
					}
				}
			}
		}
	}
end:
	return ;
}

void Mesh::subdivide()
{
	_prepare();
	std::cout << this;
	traverseOfVertex();
}
