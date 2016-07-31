/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-07-31 11:54:14
**/

#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

class Object
{
	public:
		Object();

		virtual double intersect(const Vec &, const Vec &) const = 0;

		virtual ~Object() { }

};

#endif /* _OBJECT_HPP_ */