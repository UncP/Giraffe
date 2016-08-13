/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-08-05 16:14:48
**/

#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <iterator>
#include <cassert>

#include "object.hpp"

class Triangle
{
	public:
		typedef std::vector<int32_t> Neighbor;

		Triangle() { nbr_ = {0, 0, 0}; /* nbr_.reserve(3); */ }

		const unsigned int vex(int i) const {
			assert(i >= 0 && i < 3);
			if (i == 0) return vex_[0];
			if (i == 1) return vex_[1];
			return vex_[2];
		}
		const Vector3d& norm() const { return norm_; }
/*
		const Point2i  nbr(int i) const {
			assert(i >= 0 && i < 3);
			return Point2i(nbr_[i] & 0x3FFFFFFF, (nbr_[i] >> 30) & 0x3);
		}
*/
		const int32_t nbr(int i) const {
			assert(i >= 0 && i < 3);
			return nbr_[i];
		}

		void setNormal(const Vector3d &norm) { norm_ = norm; }
		void setVertex(const Point3u &vex) 	 { vex_ = vex; }
		void setNeighbor(const int32_t triIndex, const int32_t seq) {
			// nbr_.push_back(triIndex | (seq << 30));
			assert(seq >= 0 && seq < 3);
			nbr_[seq] = triIndex;
		}

	friend
		std::ostream& operator<<(std::ostream &os, const Triangle &tri) {
			return os << tri.vex_ << tri.nbr(0) << " " << tri.nbr(1) << " " << tri.nbr(2) << std::endl;
			// return os << tri.vex_ << tri.nbr(0).x_ << " " << tri.nbr(0).y_ << "  "
			// 											<< tri.nbr(1).x_ << " " << tri.nbr(1).y_ << "  "
			// 											<< tri.nbr(2).x_ << " " << tri.nbr(2).y_ << std::endl;
		}

	private:
		Point3u 	vex_;
		Vector3d	norm_;
		Neighbor	nbr_;
};

class Vertex
{
	public:
		Vertex(const Point3d &pos):pos_(pos), tri_(-1) { }
		const Point3d& pos() const { return pos_; }
		const Point2i tri() const {
			return Point2i(tri_ & 0x3FFFFFFF, (tri_ >> 30) & 0x3);
		}
		void setTriangle(const int32_t triIndex, const int32_t index) {
			if (tri_ != -1) return ;
			tri_ = triIndex | (index << 30);
		}
	friend
		std::ostream& operator<<(std::ostream &os, const Vertex &vex) {
			return os << vex.pos_ << vex.tri().x_ << " " << vex.tri().y_ << std::endl;
		}

	private:
		Point3d  pos_;
		int32_t	 tri_;
};

class Mesh : public Object
{
	public:
		Mesh(const char *name):name_(std::string(name)) {
			_load();
		}

		void subdivide();

		bool intersect(const Ray &, Isect &) const override;

		void computeBox(std::vector<double> &, std::vector<double> &, const Vector3d *) const;

		std::ostream& print(std::ostream &) const override;

		void traverseOfVertex() const;

		Mesh(const Mesh &) = delete;
		Mesh& operator=(const Mesh &) = delete;

		~Mesh() { }

	private:
		std::string						name_;
		std::vector<Vertex> 	vertexes_;
		std::vector<Triangle>	triangles_;
		void _load();
		void _prepare();
};

#endif /* _MESH_HPP_ */