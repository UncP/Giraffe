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

#include <vector>

#include "camera.hpp"
#include "object.hpp"
#include "light.hpp"

namespace Giraffe {

class Scene
{
	public:
		Scene(const Camera *camera,
					const std::vector<Object *> &objects,
					const std::vector<Light *> lights)
		:camera_(camera), objects_(objects), lights_(lights) { }

		const Camera& camera() const { return *camera_; };
		const std::vector<Object *>& objects() const { return objects_; };
		const std::vector<Light *>& lights() const { return lights_; };

	private:
		const Camera         *camera_;
		std::vector<Object *> objects_;
		std::vector<Light *>  lights_;
};

} // namespace Giraffe

#endif /* _SCENE_HPP_ */