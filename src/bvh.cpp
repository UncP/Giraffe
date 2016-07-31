/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-07-30 20:45:46
**/

#include "bvh.hpp"

double BoundingBox::intersect(const Vec &pos, const Vec &dir) const
{
	double dis1 = std::fabs(pos.z_ - lbn_.z_);
	double dis2 = std::fabs(pos.z_ - rtf_.z_);
	double zDis = dis1 > dis2 ? dis2 : dis1;

	Vec zP = pos + zDis * dir;
	if (zP.x_ >= lbn_.x_ && zP.x_ <= rtf.x_ &&
			zP.y_ >= lbn_.y_ && zP.y_ <= rtf.y_) return zDis;

	dis1 = std::fabs(zP.x_ - lbn.x_);
	dis2 = std::fabs(zP.x_ - rtf.x_);
	double xDis = dis1 > dis2 ? dis2 : dis1;

	Vec xP = zP + xDis * dir;
	if (xP.y_ >= lbn.y_ && xP.y_<= rtf.y_ &&
			xP.z_ <= lbn.z_ && xP.z_ >= rtf.z_) return zDis + xDis;

	dis1 = std::fabs(xP.y_ - lbn.y_);
	dis2 = std::fabs(xP.y_ - rtf.y_);
	double yDis = dis1 > dis2 ? dis2 : dis1;

	Vec yP = xP + yDis * dir;
	if (yP.x_ >= lbn.x_ && yP.x_<= rtf.x_ &&
			xP.z_ <= lbn.z_ && xP.z_ >= rtf.z_) return zDis + xDis + yDis;

	return 0.0;
}