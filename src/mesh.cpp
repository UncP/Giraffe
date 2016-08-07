/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-05 16:16:15
**/

#include "mesh.hpp"

enum ObjFormat { VERTEX_ONLY = 0, VERTEX_UV, VERTEX_NORMAL, VERTEX_UV_NORMAL };

std::ostream& Mesh::print(std::ostream &os) const
{
	os << "vertexes\n";
	for (size_t i = 0; i != vertices_.size(); ++i)
		os << vertices_[i];
	os << "triangles\n";
	for (size_t i = 0; i != triangles_.size(); ++i)
		os << triangles_[i];
	return os;
}

void Mesh::load()
{
	std::ifstream in(std::string("../models/" + name_ + ".obj").c_str());
	if (!in.is_open()) {
		std::cerr << "loading mesh failed :(\n" << std::endl;
		exit(-1);
	}

	static const char *formatVertexNormal = "%d//%d";

	std::vector<Vec> 	pos;
	std::vector<Vec>	norm;

	struct Face { iVec v[3]; };
	std::vector<Face> face;

	ObjFormat format;

	std::string buf, token;
	uint32_t lineNum = 0;
	while (getline(in, buf)) {
		std::istringstream line(buf);
		line >> token;
		++lineNum;

		if (token == "v") {
			Vec v;
			line >> v.x_ >> v.y_ >> v.z_;
			if (line.fail()) {
				std::cerr << "postion syntax error in line " << lineNum << std::endl;
				exit(-1);
			}
			pos.push_back(v);
		} else if (token == "vn") {
			Vec n;
			line >> n.x_ >> n.y_ >> n.z_;
			if (line.fail()) {
				std::cerr << "normal syntax error in line " << lineNum << std::endl;
				exit(-1);
			}
			norm.push_back(n);
		} else if (token == "f") {
			std::vector<std::string> face_tokens;
			while (true) {
				std::string s;
				line >> s;
				if (line.fail()) break;
				face_tokens.push_back(s);
			}

			if (!face.size()) {
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

			Face f;
			for (size_t i = 0; i != 3; ++i) {
				iVec vi;
				switch (format) {
					case VERTEX_NORMAL:
						sscanf(face_tokens[i].c_str(), formatVertexNormal, &vi.x_, &vi.y_);
						break;
					default:
						std::cerr << "face type not supported :(\n";
						exit(-1);
						break;
				}
				f.v[i] = --vi;
			}
			face.push_back(f);
		}
		line.clear();
		token.clear();
	}

	int vertexNum = pos.size();
	int normalNum = norm.size();
	for (size_t i = 0, end = face.size(); i != end; ++i) {
		const Face &f = face[i];
		for (size_t j = 0; j != 3; ++j) {
			int vi = f.v[i][0];
			int ni = f.v[i][1];
			if (vi >= vertexNum || ni < -1 || ni >= normalNum) {
				std::cerr << "invalid index in face :(\n";
				exit(-1);
			}
		}
	}

	triangles_.reserve(face.size());
	vertices_.reserve(face.size() * 2);

	std::map<iVec, unsigned int> map;
	std::pair<std::map<iVec, unsigned int>::iterator, bool> insert;

	unsigned int index = 0;

	for (size_t i = 0, end = face.size(); i != end; ++i) {
		const Face &f = face[i];
		uVec tri;
		for (size_t j = 0; j != 3; ++j) {
			insert = map.insert({f.v[j], index});
			if (insert.second) {
				const iVec v = f.v[j];
				Vertex vertex;
				vertex.position_ = pos[v[0]];
				vertex.normal_ 	 = (v[1] == -1) ? Vec::Zero : norm[v[1]];
				vertices_.push_back(vertex);
				++index;
			}
			tri[j] = insert.first->second;
		}
		triangles_.push_back(tri);
	}

	assert(vertices_.size() == (2 * triangles_.size()));
}

void Mesh::computeBox(std::vector<double> &near, std::vector<double> &far,
	const Vec *normal) const
{
	for (size_t i = 0, iEnd = near.size(); i != iEnd; ++i)
		for (size_t j = 0, jEnd = vertices_.size(); j != jEnd; ++j) {
			double dis = dot(vertices_[j].position_, normal[i]);
			if (dis < near[i]) near[i] = dis;
			if (dis > far[i]) far[i] = dis;
		}
}

bool Mesh::intersect(const Ray &ray, Isect &isect) const
{
	bool flag = false;
	for (size_t i = 0, end = triangles_.size(); i != end; ++i) {
		const Vec &a = vertices_[triangles_[i].x_].position_;
		const Vec &b = vertices_[triangles_[i].y_].position_;
		const Vec &c = vertices_[triangles_[i].z_].position_;

		Vec a_b	(a - b);
		Vec a_c	(a - c);
		Vec a_pos(a - ray.ori_);

		Vec a_bCross_a_pos(cross(a_b, a_pos));
		Vec a_cCross_dir	 (cross(a_c, ray.dir_));

		double m = 1.0 / dot(a_b, a_cCross_dir);

		double t = dot(a_c, a_bCross_a_pos) * (-m);
		if (t < kEpsilon) continue;

		double u = dot(a_pos, a_cCross_dir) * m;
		if (u < 0.0 || u > 1.0) continue;

		double v = dot(ray.dir_, a_bCross_a_pos) * m;
		if (v < 0.0 || v > (1.0 - u)) continue;

		if (t < isect.dis_) {
			Vec hitPos = ray.ori_;
			hitPos += ray.dir_ * t;
			isect.update(t, this, hitPos, vertices_[triangles_[i].x_].normal_, kDiffuse, Vec::Zero,
				true, Vec::One);
			flag = true;
		}
	}
	return flag;
}

void Mesh::subdivide()
{

}
