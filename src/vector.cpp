/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-27 13:25:14
**/

#include "vector.hpp"

template <> Vec3 Vec3::Zero(0.0, 0.0, 0.0);
template <> Vec3 Vec3::One (1.0, 1.0, 1.0);

Color Color::Black	(Vec3::One);
Color Color::White	(Vec3::One);
Color Color::Red   	(1.0, 0.0, 0.0);
Color Color::Green 	(0.0, 1.0, 0.0);
Color Color::Blue  	(0.0, 0.0, 1.0);
Color Color::Yellow	(1.0, 1.0, 0.0);
Color Color::Purple	(1.0, 0.0, 1.0);