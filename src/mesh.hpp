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

#include "vector.hpp"
#include "vertex.hpp"

class Mesh
{
	public:
		Mesh(const char *name):name_(std::string(name)) { }

		void load();
		void print() const;

		Mesh(const Mesh &) = delete;
		Mesh& operator=(const Mesh &) = delete;
		~Mesh() { }

	private:
		std::string						name_;
		std::vector<Vex> 			vertices_;
		std::vector<uVec>		triangles_;
};

#endif /* _MESH_HPP_ */