/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-08-09 10:20:13
**/

#include "isect.hpp"

namespace Giraffe {

void Isect::update(	const double &distance,
										const Object *object,
										const Point3d &position,
										const Vector3d &normal,
										const Point2d &uv,
										const Material *material)
{
	distance_  = distance;
	object_    = object;
	vertex_    = Vertex(position, normal, uv);
	// position_  = position;
	// normal_    = normal;
	// uv_        = uv;
	material_  = material;
}

} // namespace Giraffe
