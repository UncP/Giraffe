/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-06-30 08:52:52
**/

#include <cstring>

#include "../core/tl_parser.hpp"
#include "../core/path_tracer.hpp"

int main(int argc, char **argv)
{
	using namespace Giraffe;

	int screenWidth = 512, screenHeight = 512;

	const char *dir = "../scene/";
	const char *def = "default";

	char file[128] = {0};
	strcat(file, dir);
	int samples = 1;
	if (argc == 1) {
		strcat(file, def);
	} else if (argc == 2) {
		if (!(samples = atoi(argv[1]))) {
			strcat(file, argv[1]);
			samples = 1;
		} else {
			strcat(file, def);
		}
	} else if (argc == 3) {
		samples = atoi(argv[2]);
		if (!samples) samples = 1;
		strcat(file, argv[1]);
	}
	strcat(file, ".Giraffe");
	TracingLanguageParser parser;

	Scene *scene = parser.parse(file);

	GiraffePathTracer giraffe_path_tracer(scene, screenWidth, screenHeight, samples);

	giraffe_path_tracer.ray_tracing();

	return 0;
}
