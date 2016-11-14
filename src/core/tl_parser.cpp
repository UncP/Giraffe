/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-27 21:56:51
**/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "tl_parser.hpp"

#include "../texture/constant.hpp"
#include "../texture/stripe.hpp"
#include "../texture/grid.hpp"
#include "../texture/noise.hpp"
#include "../texture/marble.hpp"
#include "../texture/brick.hpp"
#include "../texture/bump_brick.hpp"
#include "../texture/image.hpp"
#include "../texture/spot.hpp"
#include "../texture/cellular.hpp"

// #include "../material/diffuse.hpp"
// #include "../material/mirror.hpp"
// #include "../material/glossy.hpp"
// #include "../material/retro.hpp"
// #include "../material/halton.hpp"

#include "../object/plane.hpp"
#include "../object/sphere.hpp"
#include "../object/cylinder.hpp"

#include "../accelerator/box.hpp"

#include "../light/point.hpp"
#include "../light/directional.hpp"
#include "../light/area.hpp"
#include "../light/texture.hpp"

#include "../sampler/uniform.hpp"
#include "../sampler/stratified.hpp"
#include "../sampler/halton.hpp"

#include "camera.hpp"

namespace Giraffe {

Scene* TracingLanguageParser::generateScene()
{
	if (!objects_.size()) abort("no objects");
	if (!lights_.size()) abort("no lights");

	std::vector<Object *> objects;
	std::for_each(objects_.begin(), objects_.end(),
		[this, &objects] (const std::pair<std::string, std::shared_ptr<Object>> &p) {
			if (accelerated_.find(p.first) == accelerated_.end())
				objects.push_back(p.second.get());
	});
	std::vector<Light *> lights;
	std::for_each(lights_.begin(), lights_.end(),
		[&lights] (const std::pair<std::string, std::shared_ptr<Light>> &p) {
			lights.push_back(p.second.get());
	});
	return new Scene(sampler_.get(), camera_.get(), objects, lights);
}

Scene* TracingLanguageParser::parse(const char *file)
{
	std::ifstream in(file);
	if (!in.is_open()) abort("文件打开失败 ", std::string(file));
	std::string str;
	std::getline(in, str);
	for (; !in.eof() || str.size(); ++line_, str.clear(), std::getline(in, str)) {
		if (!str.size() || str.find("//") != std::string::npos)
			continue;
		slice_ = Slice(str, line_);
		std::string s(slice_.findString());
		if (s == "Texture") {
			s = slice_.findString();
			if (textures_.find(s) != textures_.end()) abort("existed texture ", s);
			textures_.insert({s, findTexture()});
		} else if (s == "Material") {
			s = slice_.findString();
			if (materials_.find(s) != materials_.end()) abort("existed material ", s);
			materials_.insert({s, findMaterial()});
		} else if (s == "Object") {
			s = slice_.findString();
			if (objects_.find(s) != objects_.end()) abort("existed object ", s);
			objects_.insert({s, findObject()});
		} else if (s == "Light") {
			s = slice_.findString();
			if (lights_.find(s) != lights_.end()) abort("existed light ", s);
				lights_.insert({s, findLight()});
		} else if (s == "Camera") {
			findCamera();
		} else if (s == "Sampler") {
			findSampler();
		} else if (s == "Accelerate") {
			s = slice_.findString();
			if (objects_.find(s) != objects_.end()) abort("conflicted name ", s);
			if (accelerators_.find(s) != accelerators_.end()) abort("existed box ", s);
			accelerators_.insert(s);
			objects_.insert({s, findBox()});
		} else {
			abort("wrong syntax ");
		}
	}
	return generateScene();
}

void TracingLanguageParser::findCamera()
{
	assert(slice_.findString() == "Perspective");
	camera_ = createPerspectiveCamera(slice_);
}

void TracingLanguageParser::findSampler()
{
	std::string s;
	s = slice_.findString();
	if (s == "Uniform")
		sampler_ = createUniformSampler(slice_);
	else if (s == "Stratified")
		sampler_ = createStratifiedSampler(slice_);
	else if (s == "Halton")
		sampler_ = createHaltonSampler(slice_);
	else
		abort("unsupported sampler");
}

std::shared_ptr<Texture> TracingLanguageParser::findTexture()
{
	std::string s(slice_.findString());
	if (s == "ConstantTexture")
		return createConstantTexture(slice_);
	else if (s == "StripeTexture")
		return createStripeTexture(slice_);
	else if (s == "GridTexture")
		return createGirdTexture(slice_);
	else if (s == "MarbleTexture")
		return createMarbleTexture(slice_);
	else if (s == "BrickTexture")
		return createBrickTexture(slice_);
	else if (s == "ImageTexture")
		return createImageTexture(slice_);
	else if (s == "BumpBrickTexture")
		return createBumpBrickTexture(slice_);
	else if (s == "SpotTexture")
		return createSpotTexture(slice_);
	else if (s == "CellularTexture")
		return createCellularTexture(slice_);
	else if (s == "NoiseTexture")
		return createNoiseTexture(slice_);
	abort("unsupported texture");
	return nullptr;
}

std::shared_ptr<Material> TracingLanguageParser::findMaterial()
{
	std::string s(slice_.findString());
	Material::Type type;
	double roughness = 0.0;
	int pow_factor = 0;
	if (s == "Diffuse") {
		type = Material::kDiffuse;
	} else if (s == "Mirror") {
		type = Material::kReflect;
	} else if (s == "Phong") {
		type = Material::kPhong;
	} else if (s == "Glossy") {
		type = Material::kGlossy;
	} else if (s == "Retro") {
		type = Material::kRetro;
	} else if (s == "Halton") {
		type = Material::kHalton;
	} else {
		abort("unsupported material ");
	}
	std::string t(slice_.findString());
	auto p = textures_.find(t);
	if (p == textures_.end()) abort("texture not existed");
	const Texture *texture = p->second.get();
	if (s == "Phong")
		pow_factor = slice_.findInteger();
	else if (s == "Glossy" || s == "Retro")
		roughness = slice_.findDouble();
	assert(slice_.eof());
	return std::shared_ptr<Material>(new Material(type, texture, roughness, pow_factor));
}

std::shared_ptr<Object> TracingLanguageParser::findObject()
{
	std::string s(slice_.findString());
	if (s == "Plane") {
		Point3d position = slice_.findPosition();
		Vector3d normal = slice_.findVector();
		s = slice_.findString();
		auto p = materials_.find(s);
		if (p == materials_.end())
			abort("material not existed");
		assert(slice_.eof());
		return std::shared_ptr<Object>(new Plane(position, normal, p->second.get()));
	} else if (s == "Sphere") {
		Point3d center = slice_.findPosition();
		double radius = slice_.findDouble();
		s = slice_.findString();
		auto p = materials_.find(s);
		if (p == materials_.end())
			abort("material not existed");
		assert(slice_.eof());
		return std::shared_ptr<Object>(new Sphere(center, radius, p->second.get()));
	} else if (s == "Cylinder") {
		Point3d center1 = slice_.findPosition();
		Point3d center2 = slice_.findPosition();
		double radius = slice_.findDouble();
		s = slice_.findString();
		auto p = materials_.find(s);
		if (p == materials_.end())
			abort("material not existed");
		assert(slice_.eof());
		return std::shared_ptr<Object>(new Cylinder(center1, center2, radius, p->second.get()));
	}
	assert(0);
}

std::shared_ptr<Light> TracingLanguageParser::findLight()
{
	std::string s(slice_.findString());
	if (s == "PointLight")
		return createPointLight(slice_);
	else if (s == "DirectionalLight")
		return createDirectionalLight(slice_);
	else if (s == "AreaLight")
		return createAreaLight(slice_);
	else if (s == "TextureLight") {
		Point3d position = slice_.findPosition();
		Vector3d direction = slice_.findVector();
		Vector3d intensity = slice_.findVector();
		double angle = slice_.findDouble();
		s = slice_.findString();
		auto p = textures_.find(s);
		if (p == textures_.end())
			abort("texture not existed");
		assert(slice_.eof());
		return std::shared_ptr<Light>(new TextureLight(position, direction, intensity, angle, \
			p->second.get()));
	}
	assert(0);
}

std::shared_ptr<Object> TracingLanguageParser::findBox()
{
	std::string name;
	std::shared_ptr<Object> box = std::shared_ptr<Object>(new AABB());
	for (; !slice_.eof();) {
		name = slice_.findString();
		auto p = objects_.find(name);
		if (p == objects_.end()) abort("objects not existed");
		accelerated_.insert(name);
		static_cast<Box *>(box.get())->put(p->second.get());
	}
	static_cast<Box *>(box.get())->enclose();
	return box;
}

} // namespace Giraffe
