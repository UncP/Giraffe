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

int getArg(int argc, char **argv, char *file)
{
	const char *dir = "../scene/";
	const char *def = "default";

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
		strcat(file, argv[1]);
		samples = atoi(argv[2]);
		if (!samples) samples = 1;
	}
	strcat(file, ".Giraffe");
	return samples;
}

int main(int argc, char **argv)
{
	using namespace Giraffe;

	int screenWidth = 512, screenHeight = 512;

	TracingLanguageParser parser;

	char file[128] = {0};
	int samples = getArg(argc, argv, file);

	Scene *scene = parser.parse(file);

	GiraffePathTracer giraffe_path_tracer(scene, screenWidth, screenHeight, samples);

	giraffe_path_tracer.path_tracing();

	return 0;
}
