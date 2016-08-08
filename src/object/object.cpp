/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-08-04 18:38:36
**/

#include "object.hpp"

std::ostream& operator<<(std::ostream &os, const Object *obj) {
	obj->print(os);
	return os;
}
