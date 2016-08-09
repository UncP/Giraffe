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

#include "../math/vertex.hpp"
#include "../object/object.hpp"

class Mesh : public Object
{
	public:
		Mesh(const char *name):name_(std::string(name)) {
			load();
		}

		void subdivide();

		bool intersect(const Ray &, Isect &) const override;

		void computeBox(std::vector<double> &, std::vector<double> &, const Vector3d *) const;

		std::ostream& print(std::ostream &) const override;

		Mesh(const Mesh &) = delete;
		Mesh& operator=(const Mesh &) = delete;

		~Mesh() { }

	private:
		std::string							name_;
		std::vector<Vertex> 		vertices_;
		std::vector<Point3u>		triangles_;
		void load();
};

#endif /* _MESH_HPP_ */