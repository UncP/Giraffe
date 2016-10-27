/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-27 21:56:51
**/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "tl_parser.hpp"

namespace Giraffe {

bool TracingLanguageParser::parse(const char *file)
{
	std::ifstream in(file);
	if (!in.is_open()) {
		std::cerr << "文件打开失败 :(\n";
		return false;
	}

	char buf[4096], *str = buf;
	in.getline(str, 4096);
	for (; strlen(str); in.getline(str, 4096)) {

	}
	return false;
}

} // namespace Giraffe
