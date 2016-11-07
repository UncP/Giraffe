/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-06 18:24:52
**/

#ifndef _GIRAFFE_PATHTRACER_HPP_
#define _GIRAFFE_PATHTRACER_HPP_

#include "../math/ray.hpp"
#include "scene.hpp"

namespace Giraffe {

class GiraffePathTracer
{
	public:

		GiraffePathTracer(const Scene *scene, const int height, const int width, const int sample);

		Vector3d trace(const Ray &ray, int depth);

		void ray_tracing();

		~GiraffePathTracer();

	private:

		void save_png() const;

		void save_ppm() const;

		const Scene   *scene_;
		Vector3d      *pixels_;
		int            width_;
		int	           height_;
		int            samples_;
};

} // namespace Giraffe

#endif /* _GIRAFFE_PATHTRACER_HPP_ */