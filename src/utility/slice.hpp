/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-11-14 16:49:42
**/

#ifndef _SLICE_HPP_
#define _SLICE_HPP_

#include <string>
#include <sstream>

#include "../math/point.hpp"
#include "../math/vector.hpp"
#include "../math/matrix.hpp"

namespace Giraffe {

class Slice
{
	public:
		Slice() { }

		Slice(const std::string &str, int line):str_(std::istringstream(str)), line_(line) { }

		bool eof() { return str_.eof(); }

		std::string findString();

		Point3d findPosition();

		Vector3d findVector();

		double findDouble();

		int findInteger();

		int findAxis();

		bool findBool();

		Matrix findMatrix();

	private:
		void check() const {
			if (str_.fail()) {
				std::cout << "line " << line_ << ": syntax error:(\n";
				exit(-1);
			}
		}

		void abort(const std::string &error, const std::string &s = "") const {
			std::cerr << "line " << line_ << ": " << error << s << " :(\n";
			exit(-1);
		}

		std::istringstream str_;
		int                line_;

};

} // namespace Giraffe

#endif /* _SLICE_HPP_ */