/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-27 21:56:11
**/

#ifndef _TL_PARSER_HPP_
#define _TL_PARSER_HPP_

#include <set>
#include <map>
#include <memory>
#include <sstream>

#include "../utility/slice.hpp"
#include "scene.hpp"
#include "texture.hpp"
#include "object.hpp"
#include "light.hpp"
#include "material.hpp"

namespace Giraffe {

class TracingLanguageParser
{
	public:

		TracingLanguageParser():line_(1) { }

		Scene* parse(const char *file);

	private:
		void abort(const std::string &error, const std::string &s = "") const {
			std::cerr << "line " << line_ << ": " << error << s << " :(\n";
			exit(-1);
		}

		void findCamera();

		void findSampler();

		std::shared_ptr<Texture> findTexture();

		std::shared_ptr<Material> findMaterial();

		std::shared_ptr<Object> findObject();

		std::shared_ptr<Light> findLight();

		std::shared_ptr<Object> findBox();

		Scene* generateScene();

		int line_;
		Slice slice_;
		std::shared_ptr<Sampler>                         sampler_;
		std::shared_ptr<Camera>                          camera_;
		std::map<std::string, std::shared_ptr<Texture>>  textures_;
		std::map<std::string, std::shared_ptr<Material>> materials_;
		std::map<std::string, std::shared_ptr<Object>>   objects_;
		std::set<std::string>                            accelerated_;
		std::set<std::string>                            accelerators_;
		std::map<std::string, std::shared_ptr<Light>>    lights_;
};

} // namespace Giraffe

#endif /* _TL_PARSER_HPP_ */