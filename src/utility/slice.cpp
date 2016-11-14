/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-14 16:51:05
**/

#include <cassert>

#include "slice.hpp"

namespace Giraffe {

std::string Slice::findString()
{
	std::string s;
	str_ >> s;
	check();
	return s;
}

Point3d Slice::findPosition()
{
	std::string s;
	str_ >> s;
	assert(s == "Position");
	Point3d res;
	str_ >> res.x_ >> res.y_ >> res.z_;
	check();
	return res;
}

Vector3d Slice::findVector()
{
	std::string s;
	str_ >> s;
	assert(s == "Normal" || s == "Color" || s == "Direction" || s == "Intensity");
	Vector3d res;
	str_ >> res.x_ >> res.y_ >> res.z_;
	check();
	return res;
}

double Slice::findDouble()
{
	double res;
	str_ >> res;
	check();
	return res;
}

int Slice::findInteger()
{
	int res;
	str_ >> res;
	check();
	return res;
}

int Slice::findAxis()
{
	std::string s;
	str_ >> s;
	if (s == "Xaxis") return Xaxis;
	if (s == "Yaxis") return Yaxis;
	if (s == "Zaxis") return Zaxis;
	abort("wrong axis ");
	return 0;
}

bool Slice::findBool()
{
	std::string s;
	str_ >> s;
	if (s == "true") return true;
	if (s == "false") return false;
	abort("wrong bool ");
	return 0;
}

Matrix Slice::findMatrix()
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
		abort("wrong matrix ");
	double angle = findDouble();
	check();
	return transform(angle);
}

} // namespace Giraffe
