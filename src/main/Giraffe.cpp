/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-06-30 08:52:52
**/

#include "../core/tl_parser.hpp"
#include "../core/path_tracer.hpp"

int main(int argc, char **argv)
{
	using namespace Giraffe;

	int screenWidth = 512, screenHeight = 512;

	const char *file = "../scene/default.Giraffe";
	if (argc == 3) file = argv[1];
	TracingLanguageParser parser;
	Scene *scene = parser.parse(file);

	int samples = 1;
	if (argc == 2) samples = atoi(argv[1]);
	else if (argc == 3) samples = atoi(argv[2]);
	GiraffePathTracer giraffe_path_tracer(scene, screenWidth, screenHeight, samples);

	giraffe_path_tracer.ray_tracing();

	delete scene;
	return 0;
}
