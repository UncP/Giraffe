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

#include "tl_parser.hpp"

#include "../texture/stripe.hpp"
#include "../texture/noise.hpp"
#include "../texture/marble.hpp"
#include "../texture/brick.hpp"
#include "../texture/image.hpp"

#include "../material/diffuse.hpp"

#include "../object/plane.hpp"
#include "../object/sphere.hpp"
#include "../object/cylinder.hpp"

#include "../light/point.hpp"
#include "../light/directional.hpp"
#include "../light/area.hpp"
#include "../light/texture.hpp"

#include "camera.hpp"

namespace Giraffe {

void TracingLanguageParser::check() const
{
	if (str_.fail()) {
		std::cout << "line " << line_ << ": syntax error:(\n";
		exit(-1);
	}
}

void TracingLanguageParser::abort(const std::string &error, const std::string &s) const
{
	std::cerr << "line " << line_ << ": " << error << s << " :(\n";
	exit(-1);
}

Scene* TracingLanguageParser::parse(const char *file)
{
	std::ifstream in(file);
	if (!in.is_open()) abort("文件打开失败");

	std::string str;
	std::getline(in, str);
	for (; !in.eof() || str.size(); ++line_, str.clear(), std::getline(in, str)) {
		if (!str.size() || str.find("//") != std::string::npos)
			continue;
		str_ = std::istringstream(str);
		std::string s;
		str_ >> s;
		if (s == "Texture") {
			str_ >> s;
			if (textures_.find(s) != textures_.end()) abort("existed texture", s);
			textures_.insert({s, findTexture()});
		} else if (s == "Material") {
			str_ >> s;
			if (materials_.find(s) != materials_.end()) abort("existed material", s);
			materials_.insert({s, findMaterial()});
		} else if (s == "Object") {
			str_ >> s;
			if (objects_.find(s) != objects_.end()) abort("existed object", s);
			objects_.insert({s, findObject()});
		} else if (s == "Light") {
			str_ >> s;
			if (lights_.find(s) != lights_.end()) abort("existed light", s);
				lights_.insert({s, findLight()});
		} else {
			abort("wrong type");
		}
	}
	if (!objects_.size()) abort("no objects");
	if (!lights_.size()) abort("no lights");

	std::vector<Object *> objects;
	std::for_each(objects_.begin(), objects_.end(),
		[&objects] (const std::pair<std::string, std::shared_ptr<Object>> &p) {
			assert(p.second);
			objects.push_back(p.second.get());
	});
	std::vector<Light *> lights;
	std::for_each(lights_.begin(), lights_.end(),
		[&lights] (const std::pair<std::string, std::shared_ptr<Light>> &p) {
			assert(p.second);
			lights.push_back(p.second.get());
	});

	int screenWidth = 512, screenHeight = 512;
	camera_ = std::shared_ptr<Camera>(
		new PerspectiveCamera(Point3d(0, 0, 0), \
													Vector3d(0, 0, -1.0), \
													Point2i(screenWidth, screenHeight), \
													Point2i(screenWidth, screenHeight), \
													90));

	return new Scene(camera_.get(), objects, lights);
}

Point3d TracingLanguageParser::findPosition()
{
	std::string s;
	str_ >> s;
	assert(s == "Position");
	Point3d res;
	str_ >> res.x_ >> res.y_ >> res.z_;
	check();
	return res;
}

Vector3d TracingLanguageParser::findVector()
{
	std::string s;
	str_ >> s;
	assert(s == "Normal" || s == "Color" || s == "Direction" || s == "Intensity");
	Vector3d res;
	str_ >> res.x_ >> res.y_ >> res.z_;
	check();
	return res;
}

std::string TracingLanguageParser::findString()
{
	std::string res;
	str_ >> res;
	if (res.size() < 3 || res[0] != '\"' || res[res.size() - 1] != '\"')
		return std::string();
	check();
	return std::string(res.begin() + 1, res.end() - 1);
}

double TracingLanguageParser::findDouble()
{
	double res;
	str_ >> res;
	check();
	return res;
}

int TracingLanguageParser::findInteger()
{
	int res;
	str_ >> res;
	check();
	return res;
}

int TracingLanguageParser::findAxis()
{
	std::string s;
	str_ >> s;
	if (s == "Xaxis") return Xaxis;
	if (s == "Yaxis") return Yaxis;
	if (s == "Zaxis") return Zaxis;
	abort("find axis failed");
	return 0;
}

bool TracingLanguageParser::findBool()
{
	std::string s;
	str_ >> s;
	if (s == "true") return true;
	if (s == "false") return false;
	abort("find bool failed");
	return 0;
}

Matrix TracingLanguageParser::findMatrix()
{
	std::string s;
	str_ >> s;
	Matrix (*transform)(double) = nullptr;
	if (s == "rotateX")
		transform = rotateX;
	else if (s == "rotateY")
		transform = rotateY;
	else if (s == "rotateZ")
		transform = rotateZ;
	else
		abort("find matrix failed");
	double angle = findDouble();
	check();
	return transform(angle);
}

std::shared_ptr<Texture> TracingLanguageParser::findTexture()
{
	std::string s;
	str_ >> s;
	Matrix matrix = Matrix::Identity;
	if (s == "StripeTexture") {
		Vector3d color1 = findVector();
		Vector3d color2 = findVector();
		int axis = findAxis();
		double factor = findDouble();
		if (!str_.eof()) {
			matrix = findMatrix();
			assert(str_.eof());
		}
		return std::shared_ptr<Texture>(
			new StripeTexture(color1, color2, axis, factor, matrix));
	} else if (s == "MarbleTexture") {
		Vector3d color1 = findVector();
		Vector3d color2 = findVector();
		Vector3d color3 = findVector();
		double frequency = findDouble();
		assert(str_.eof());
		return std::shared_ptr<Texture>(
			new MarbleTexture(color1, color2, color3, frequency));
	} else if (s == "BrickTexture") {
		Vector3d color1 = findVector();
		Vector3d color2 = findVector();
		double width = findDouble();
		double height = findDouble();
		double interval = findDouble();
		assert(str_.eof());
		return std::shared_ptr<Texture>(
			new BrickTexture(color1, color2, width, height, interval));
	} else if (s == "ImageTexture") {
		std::string file = findString();
		if (str_.fail() || !file.size()) return nullptr;
		double frequency = findDouble();
		assert(str_.eof());
		return std::shared_ptr<Texture>(new ImageTexture(file.c_str(), frequency));
	}
	assert(0);
}

std::shared_ptr<Material> TracingLanguageParser::findMaterial()
{
	std::string s;
	str_ >> s;
	if (s == "Diffuse") {
		Vector3d color = findVector();
		assert(str_.eof());
		return std::shared_ptr<Material>(new Diffuse(color));
	}
	assert(0);
}

std::shared_ptr<Object> TracingLanguageParser::findObject()
{
	std::string s;
	str_ >> s;
	if (s == "Plane") {
		Point3d position = findPosition();
		Vector3d normal = findVector();
		str_ >> s;
		auto p = materials_.find(s);
		if (p == materials_.end())
			abort("material not existed");
		assert(str_.eof());
		return std::shared_ptr<Object>(new Plane(position, normal, p->second.get()));
	} else if (s == "Sphere") {
		Point3d center = findPosition();
		double radius = findDouble();
		str_ >> s;
		auto p = materials_.find(s);
		if (p == materials_.end())
			abort("material not existed");
		assert(str_.eof());
		return std::shared_ptr<Object>(new Sphere(center, radius, p->second.get()));
	} else if (s == "Cylinder") {
		Point3d center1 = findPosition();
		Point3d center2 = findPosition();
		double radius = findDouble();
		str_ >> s;
		auto p = materials_.find(s);
		if (p == materials_.end())
			abort("material not existed");
		assert(str_.eof());
		return std::shared_ptr<Object>(new Cylinder(center1, center2, radius, p->second.get()));
	}
	assert(0);
}

std::shared_ptr<Light> TracingLanguageParser::findLight()
{
	std::string s;
	str_ >> s;
	if (s == "PointLight") {
		Point3d position = findPosition();
		Vector3d intensity = findVector();
		assert(str_.eof());
		return std::shared_ptr<Light>(new PointLight(position, intensity));
	} else if (s == "DirectionalLight") {
		Vector3d direction = findVector();
		Vector3d intensity = findVector();
		return std::shared_ptr<Light>(new DirectionalLight(direction, intensity));
	} else if (s == "AreaLight") {
		Point3d position = findPosition();
		Vector3d direction = findVector();
		Vector3d intensity = findVector();
		double angle = findDouble();
		return std::shared_ptr<Light>(new AreaLight(position, direction, intensity, angle));
	} else if (s == "TextureLight") {
		Point3d position = findPosition();
		Vector3d direction = findVector();
		Vector3d intensity = findVector();
		double angle = findDouble();
		str_ >> s;
		auto p = textures_.find(s);
		if (p == textures_.end())
			abort("texture not existed");
		assert(str_.eof());
		return std::shared_ptr<Light>(new TextureLight(position, direction, intensity, angle, \
			p->second.get()));
	}
	assert(0);
}

} // namespace Giraffe
