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
#include "bvh.hpp"

class Scene
{
	public:
		static Scene CornellBox;
		static Scene DepthOfField;
		static Scene MotionBlur;

		Scene(const char *name, const int width, const int height, Camera *camera,
					const std::vector<Object *> &objects)
		:name_(name), width_(width), height_(height), camera_(camera), objects_(objects) { }

		void accelerate();

		const std::string& name() const { return name_; }
		const Camera& camera() const { return *camera_; };
		const std::vector<Object *>& objects() const { return objects_; };
		const int width() const  { return width_; }
		const int height() const { return height_; }

		~Scene() {
			delete camera_;
			if (!accelerate_)
				std::for_each(objects_.begin(), objects_.end(), [](Object *obj) { delete obj; });
		}

	private:
		std::string 					name_;
		int 									width_, height_;
		bool 									accelerate_ = false;
		Camera 							 *camera_;
		std::vector<Object *> objects_;
};

#endif /* _SCENE_HPP_ */