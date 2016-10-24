/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-06-30 08:52:52
**/

#include <memory>

#include "../math/matrix.hpp"
#include "../core/scene.hpp"
#include "../core/window.hpp"
#include "../object/sphere.hpp"
#include "../object/triangle.hpp"
#include "../object/cube.hpp"
#include "../object/cylinder.hpp"
#include "../object/disk.hpp"
#include "../texture/constant.hpp"
#include "../texture/stripe.hpp"
#include "../texture/noise.hpp"
#include "../texture/marble.hpp"
#include "../texture/brick.hpp"
#include "../texture/image.hpp"
#include "../texture/bump_brick.hpp"
#include "../light/point.hpp"
#include "../light/directional.hpp"
#include "../light/area.hpp"
#include "../light/texture.hpp"

int main(int argc, char **argv)
{
	using namespace Giraffe;

	typedef std::shared_ptr<Texture> Tex;
	typedef Point3d  Pos;
	typedef Vector3d Dir;
	typedef Vector3d Int;
	typedef Vector3d Color;

	int screenWidth = 512, screenHeight = 512;
	Camera *camera = new PerspectiveCamera(	Pos(0, 0, 0), Dir(0, 0, -1.0),\
																					Point2i(screenWidth, screenHeight), \
																					Point2i(screenWidth, screenHeight), \
																					90);

		// new StripeTexture(Color(), Color(1), Xaxis, 3));
		// new BrickTexture(Color(0.75, 0.25, 0.25), Color(0.5), 1.2e-4, 4.8e-5, 7.2e-6));
		// new MarbleTexture(Color(0.8), Color(0.75, 0.25, 0.25), Color(0.05), 0.1));
		// new ImageTexture("../Tex/earth.png"));
		// new MarbleTexture(Color(1), Color(4, 1, 2), Color(0.5), 0.2, true));
	Tex mirror= Tex(new ConstantTexture(Color(0.99), false, kReflect));
	Tex glass = Tex(new ConstantTexture(Color(0.99), false, kRefract));

	Tex wall1 = Tex(new ConstantTexture(Color(0.75)));
	Tex wall2 = Tex(new ConstantTexture(Color(0)));
	Tex wall3 = Tex(new ConstantTexture(Color(0.75, 0.25, 0.25)));
	Tex wall4 = Tex(new ConstantTexture(Color(0.25, 0.75, 0.25)));
	Tex wall5 = Tex(new BrickTexture(Color(0.1, 0.1, 0.5), Color(0.5),
		1.2e-4, 4.8e-5, 7.2e-6, shear2X(45)));

	Tex tex1 = Tex(new ConstantTexture(Color(0.8)));
	Tex tex2 = Tex(new ConstantTexture(Color(0.3)));
	Tex tex3 = Tex(new ConstantTexture(Color(0.8)));
	Tex tex4 = Tex(new ConstantTexture(Color(0.15)));
	Tex tex5 = Tex(new ConstantTexture(Color(0.9, 0.2, 0.2)));
	Tex tex6 = Tex(new ConstantTexture(Color(0.2)));
	Tex tex7 = Tex(new ImageTexture("../texture/stones.png", 1, true));
	// Tex tex8 = Tex(new ImageTexture("../image/bear.png", 1, true));

	// Tex tex9 = Tex(new StripeTexture(Color(0.6, 0.6, 0.2), Color(0.2, 0.6, 0.6), Xaxis,
	// 	5, Matrix::Identity, true));

	Tex light= Tex(new ConstantTexture(Color(16), true));

	std::vector<Object *> objects = {
		new Sphere(Pos(0, -10, -160), 20, tex1),

		new Sphere(Pos(0, -1e5-60, -160),		1e5, 	wall1),
		new Sphere(Pos(0, 1e5+60, -160), 		1e5, 	wall1),
		new Sphere(Pos(0, 0, -1e5-225), 		1e5, 	wall1),
		new Sphere(Pos(-1e5-70, 0, -175), 	1e5, 	wall3),
		new Sphere(Pos(1e5+70, 0, -175),  	1e5, 	wall4),
		new Sphere(Pos(0, 959.8, -160.0), 	900, 	light)
	};

	std::vector<Light *> lights = {
		// new PointLight(Pos(0, 59.9999, -160.0), Int(2048)),
		// new PointLight(Pos(-50, 30, -180.0), Int(256)),
		// new PointLight(Pos(50, 30, -140.0), Int(256))
		// new DirectionalLight(Dir(-0.3, 0.3, -1), Int(0.8))
		// new AreaLight(Pos(0, 50, -160.0), Dir(0, -1, 0), Int(2048), 30)
		// new TextureLight(Pos(-50, 50, -50), Dir(0.8, -1.0, -2), Int(1.5), 20, tex7)
		new TextureLight(Pos(-20, 0, -50), Dir(0.2, 0, -1), Int(1.5), 20, tex7)
	};

	Scene CornellBox("cornell box", camera, objects, lights);

	Window win(CornellBox.name(), screenWidth, screenHeight);

	win.ray_tracing(CornellBox, argc == 2 ? atoi(argv[1]) : 1);

	return 0;
}
