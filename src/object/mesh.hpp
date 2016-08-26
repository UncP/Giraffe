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
#include <set>
#include <cassert>

#include "object.hpp"

class MeshTriangle;
class MeshEdge;

class MeshVertex
{
	public:
		MeshVertex(const Point3f &pos):pos_(pos) { }

		const Point3f& pos() const { return pos_; }

		void setEdge(MeshEdge *e) { edge_ = e; }

		bool operator==(const MeshVertex &v) const {
			return pos_ == v.pos_;
		}
		bool operator<(const MeshVertex &v) const {
			return pos_ < v.pos_;
		}

	friend
		std::ostream& operator<<(std::ostream &os, const MeshVertex &v) {
			return os << v.pos_;
		}
	private:
		Point3f 			pos_;
		MeshEdge 		 *edge_ = nullptr;
};

class MeshTriangle
{
	public:
		MeshTriangle(const Vector3f &normal):normal_(normal){ }

		void setEdge(MeshEdge *e) { edge_ = e; }

	private:
		Vector3f 		 normal_;
		MeshEdge 		 *edge_ = nullptr;
};

class MeshEdge
{
	public:
		MeshEdge(MeshVertex *head, MeshVertex *tail):head_(head), tail_(tail) { }

		void setFace(MeshTriangle *t) {
			if (!left_) left_  = t;
			else 				right_ = t; }

		bool operator<(const MeshEdge &e) const {
			if (*head_ == *e.head_) return *tail_ < *e.tail_;
			return *head_ < *e.head_;
		}

		MeshEdge& operator=(const MeshEdge &e) {
			lprev_ = e.lprev_, lnext_ = e.lnext_, rprev_ = e.rprev_, rnext_ = e.rnext_;
			head_ = e.head_, tail_  = e.tail_;
			left_ = e.left_, right_ = e.right_;
			return *this;
		}

	friend
		std::ostream& operator<<(std::ostream &os, const MeshEdge &edge) {
			return os << "head " << *edge.head_ << "tail " << *edge.tail_;
		}
	private:
		MeshEdge		 *lprev_ = nullptr, *lnext_ = nullptr, *rprev_ = nullptr, *rnext_ = nullptr;
		MeshVertex	 *head_ = nullptr, *tail_ = nullptr;
		MeshTriangle *left_ = nullptr, *right_ = nullptr;
};

class Mesh : public Object
{
	public:
		Mesh(const char *name):name_(std::string(name)) {
			load();
		}

		void subdivide();

		bool intersect(const Ray &, Isect &) const override;

		// void computeBox(std::vector<double> &, std::vector<double> &, const Vector3d *) const;

		std::ostream& print(std::ostream &) const override;

		Mesh(const Mesh &) = delete;
		Mesh& operator=(const Mesh &) = delete;

		~Mesh() { }

	private:
		std::string									name_;
		std::vector<MeshVertex *> 	vertexes_;
		std::vector<MeshTriangle *> triangles_;
		std::set<MeshEdge> 					edges_;
		void load();
};

#endif /* _MESH_HPP_ */