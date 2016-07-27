/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-27 20:39:07
**/

#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <string>
#include <vector>

#include "sphere.hpp"
#include "camera.hpp"

class Scene
{
	public:
		static Scene CornellBox;

		Scene(const char *name, const Camera &camera, const std::vector<Sphere *> &spheres)
		:name_(name), camera_(camera), spheres_(spheres) { }
		Scene(const Scene &s):name_(s.name_), camera_(s.camera_), spheres_(s.spheres_) { }

		const std::string& name() const { return name_; }
		const Camera& camera() const { return camera_; };
		const std::vector<Sphere *>& sphere()  const { return spheres_; };

		~Scene() { }
	private:
		std::string 					name_;
		Camera 								camera_;
		std::vector<Sphere *> spheres_;
};

#endif /* _SCENE_HPP_ */