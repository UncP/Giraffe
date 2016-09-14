/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-07-27 20:39:07
**/

#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <string>
#include <vector>

#include "../object/sphere.hpp"
#include "../accelerator/bvh.hpp"
#include "camera.hpp"

class Scene
{
	public:
		Scene(const char *name, Camera *camera, const std::vector<Object *> &objects)
		:name_(name), accelerate_(false), camera_(camera), objects_(objects) { }

		void accelerate();

		const std::string& name() const { return name_; }
		const Camera& camera() const { return *camera_; };
		const std::vector<Object *>& objects() const { return objects_; };

		~Scene();

	private:
		std::string 					name_;
		bool 									accelerate_;
		Camera 							 *camera_;
		std::vector<Object *> objects_;
};

#endif /* _SCENE_HPP_ */