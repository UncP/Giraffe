/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-03 20:16:46
**/

#ifndef _RAY_HPP_
#define _RAY_HPP_

#include "point.hpp"
#include "vector.hpp"

class Ray
{
	public:
		Ray(const Point3d &ori, const Vector3d &dir):ori_(ori), dir_(dir) { }

		void setDirection(const Vector3d &dir) { dir_ = dir; }
		void setOrigin(const Point3d &ori) { ori_ = ori; }

		const Vector3d& direction() const { return dir_; }
		const Point3d&  origin()    const { return ori_; }

	private:
		Point3d 	ori_;
		Vector3d 	dir_;
	friend std::ostream& operator<<(std::ostream &os, const Ray &ray) {
		return os << "ori " << ray.ori_ << "dir " << ray.dir_;
	}
};

#endif /* _RAY_HPP_ */