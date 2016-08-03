/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-30 17:18:13
**/

#include "window.hpp"

static void _findHitObject(const Ray &ray, const std::vector<Object *> &objects, Isect &isect)
{
	for (size_t i = 0, end = objects.size(); i != end; ++i)
		objects[i]->intersect(ray, isect);
}

static Vec trace(const Ray &ray, const std::vector<Object *> &objects, int depth)
{
	Isect isect;
	_findHitObject(ray, objects, isect);
	if (isect.miss()) return Vec();

	Object *obj = isect.obj_;
	Vec color(obj->color());
	double max = std::max(color.x_, std::max(color.y_, color.z_));
	if (++depth > 5) {
		if (Random() < max) color *= (1.0 / max);
		else return obj->emission();
	}

	Vec pos = ray.ori_ + ray.dir_ * isect.dis_;
	Vec normal = pos - obj->center();
	normalize(normal);

	bool into = true;
	if (dot(ray.dir_, normal) > 0) normal = -normal, into = false;

	Vec reflPos = pos + normal * kEpsilon;
	REFL mat = obj->refl();

	if (mat == kDiffuse) {
		Vec u, v, w(normal);
		if (std::fabs(w.x_) > 0.1)
			u = cross(Vec(0, 1, 0), w);
		else
			u = cross(Vec(1, 0, 0), w);
		normalize(u);
		v = cross(w, u);
		normalize(v);
		double a = Random(), b = Random(), sini = std::sqrt(a), cosi = DOU_PI * b;
		Vec dir((sini*std::cos(cosi)*u) + (sini*std::sin(cosi)*v) + (std::sqrt(1-a)*w));
		normalize(dir);

		// Vec c;
		// for (int i = 0, end = objects.size(); i != end; ++i) {
		// 	if (!objects[i]->emit() || objects[i] == obj) continue;
		// 	Vec newDir(objects[i]->center() - obj->center());
		// 	normalize(newDir);
		// 	Object *obj;
		// 	if (!(obj = Ray(pos, newDir).intersect(objects, near)) || obj == objects[i])
		// 		c += objects[i]->emission() * color * std::max(0.0, dot(newDir, normal));
		// }

		return obj->emission() + color * trace(Ray(reflPos, dir), objects, depth);
	}

	Vec refl = ray.dir_ - 2 * dot(ray.dir_, normal) * normal;
	normalize(refl);

	if (mat == kReflect)
		return obj->emission() + color * trace(Ray(reflPos, refl), objects, depth);

	double etai = 1.0, etat = kRefractionRatio;
	double ior;
	if (into) ior = 1.0 / kRefractionRatio;
	else 			ior = kRefractionRatio;

	double cos1 = -dot(ray.dir_, normal), cos2;
	if ((cos2 = (1 - ior * ior * (1.0 - cos1 * cos1))) < 0.0)
		return obj->emission() + color * trace(Ray(reflPos, refl), objects, depth);

	Vec refr(ray.dir_ * ior + normal * (ior * cos1 - std::sqrt(cos2)));
	Vec refrPos = pos - normal * kEpsilon;
	normalize(refr);

	double a = etat - etai, b = etat + etai;
	double R0 = a * a / (b * b), c = 1 - (into ? cos1 : -dot(refr, normal));
	double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re;

	double P = 0.25 + 0.5 * Re, RP = Re / P, TP = Tr / (1 - P);
	return obj->emission() + color * (depth > 2 ? (Random() < P ?
		trace(Ray(reflPos, refl), objects, depth)*RP:trace(Ray(refrPos, refr), objects, depth)*TP):
		trace(Ray(reflPos, refl), objects, depth)*Re+trace(Ray(refrPos, refr), objects, depth)*Tr);
}

void Window::render(const Scene &scene, const int &samples)
{
	const Camera &camera = scene.camera();
	const std::vector<Object *> &spheres = scene.objects();
	double inv = 1.0 / samples;
	Vec color;
	auto beg = std::chrono::high_resolution_clock::now();

	#pragma omp parallel for schedule(dynamic, 1) private(color)
	for (int x = 0; x < width_; ++x) {
		fprintf(stderr,"\rprogress: %5.2f%%", 100 * (x / static_cast<float>(width_-1)));
		for (int y = 0; y < height_; ++y) {
			for (int sx = 0, i = x + y * width_; sx < 2; ++sx) {
				for (int sy = 0; sy < 2; ++sy, color = Vec()) {
					for (int n = 0; n < samples; ++n) {
						double a = Random(), b = Random();
						Ray ray = camera.computeRay(x+(a+sx+0.5)*0.5, y+(b+sy+0.5)*0.5);
						color += trace(ray, spheres, 0) * inv;
					}
					pixels_[i] += color * 0.25;
				}
			}
		}
	}

	auto end  = std::chrono::high_resolution_clock::now();
	auto Time = std::chrono::duration<double, std::milli>(end - beg).count();
	std::cout << "\ntime: " << setw(8) << (Time / 1000) << "  s\n";

	show();
	save_png(title_);
}

void Window::show() const {
	for (int i = 0, end = width_ * height_; i < end; ++i) {
		canvas_[i] = 0;
		canvas_[i] |= 0xFF << 24;
		canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].x_, 1.0) * 255.0) << 16;
		canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].y_, 1.0) * 255.0) << 8;
		canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].z_, 1.0) * 255.0);
	}
	SDL_UpdateRect(screen_, 0, 0, 0, 0);
	getchar();
}

void Window::save_ppm(const char *name) const {
	char file[32];
	strcpy(file, name);
	strcat(file, ".png");
	std::ofstream out(file, std::ios::out | std::ios::binary);
	if (!out) { std::cerr << "ppm格式图片保存失败 :(\n"; return ; }
	out << "P3\n" << width_ << " " << height_ << "\n255\n";
	for (int i = 0, end = width_ * height_; i < end; ++i) {
		int r = static_cast<int>(std::pow(std::min(pixels_[i].x_,1.0),1 / 2.2) * 255 + 0.5);
		int g = static_cast<int>(std::pow(std::min(pixels_[i].y_,1.0),1 / 2.2) * 255 + 0.5);
		int b = static_cast<int>(std::pow(std::min(pixels_[i].z_,1.0),1 / 2.2) * 255 + 0.5);
		out << r << " " << g << " " << b << " ";
	}
	out.close();
}

bool Window::save_png(const char *name) const
{
	char file[32];
	strcpy(file, name);
	strcat(file, ".png");
	FILE *fp = fopen(file, "wb");
	if (!fp) return false;

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if (!png_ptr) {
		std::cerr << "png格式图片保存失败 :(\n";
		fclose(fp);
		return false;
	}
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, (png_infopp) 0);
		std::cerr << "png格式图片保存失败 :(\n";
		fclose(fp);
		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		std::cerr << "png格式图片保存失败 :(\n";
		fclose(fp);
		return false;
	}

	png_init_io(png_ptr, fp);

	png_set_IHDR(png_ptr, info_ptr, width_, height_, 8, PNG_COLOR_TYPE_RGB_ALPHA,
	  PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);
	png_set_flush(png_ptr, 10);

	unsigned char *pic = new unsigned char[height_ * width_ * 4];
	if (!pic) {
		std::cerr << "png格式图片保存失败 :(\n";
		return false;
	}

	for (int i = 0, end = width_ * height_; i < end; ++i) {
		canvas_[i] = 0;
		canvas_[i] |= 0xFF << 24;
		canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].z_, 1.0) * 255.0) << 16;
		canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].y_, 1.0) * 255.0) << 8;
		canvas_[i] |= static_cast<uint8_t>(std::min(pixels_[i].x_, 1.0) * 255.0);
	}

	memcpy(pic, static_cast<void *>(canvas_), height_ * width_ * 4);
	png_bytep *row_pointers = new png_bytep[height_];
	if (!row_pointers) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		std::cerr << "png格式图片保存失败 :(\n";
		return false;
	}
	for (int y = 0; y < height_; ++y)
		row_pointers[y] = static_cast<png_byte *>(pic + y * width_ * 4);
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, info_ptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	delete [] row_pointers;
	delete [] pic;
	return true;
}
