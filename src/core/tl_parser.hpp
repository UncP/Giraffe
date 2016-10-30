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

#include <map>
#include <memory>
#include <sstream>

#include "../math/point.hpp"
#include "../math/vector.hpp"
#include "../math/matrix.hpp"
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

		Point3d findPosition();

		Vector3d findVector();

		double findDouble();

		int findInteger();

		int findAxis();

		std::string findString();

		bool findBool();

		Matrix findMatrix();

		void check() const;

		void abort(const std::string &, const std::string & = "") const;

		std::shared_ptr<Texture> findTexture();

		std::shared_ptr<Material> findMaterial();

		std::shared_ptr<Object> findObject();

		std::shared_ptr<Light> findLight();

		int line_;
		std::istringstream str_;
		std::shared_ptr<Camera> camera_;
		std::map<std::string, std::shared_ptr<Texture>>  textures_;
		std::map<std::string, std::shared_ptr<Material>> materials_;
		std::map<std::string, std::shared_ptr<Object>>   objects_;
		std::map<std::string, std::shared_ptr<Light>>    lights_;
};

} // namespace Giraffe

#endif /* _TL_PARSER_HPP_ */