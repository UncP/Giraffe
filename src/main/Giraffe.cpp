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
	const char *def = "default.Giraffe";
	char file[128] = {0};
	strcat(file, dir);
	if (argc == 3)
		strcat(file, argv[1]);
	else
		strcat(file, def);
	TracingLanguageParser parser;
	Scene *scene = parser.parse(file);

	int samples = 1;
	if (argc == 2) samples = atoi(argv[1]);
	GiraffePathTracer giraffe_path_tracer(scene, screenWidth, screenHeight, samples);

	giraffe_path_tracer.ray_tracing();

	delete scene;
	return 0;
}
