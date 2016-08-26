/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-07-30 17:18:13
**/

#include "window.hpp"

Window::Window(const std::string &title, const int width, const int height)
:title_(title), width_(width), height_(height), pixels_(new Vector3d[width_*height_])
{	// canvas_(new uint32_t[width_*height_])
	if (!pixels_) {
		std::cerr << "像素初始化失败 :(\n";
		exit(-1);
	}

	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "SDL_Init failed :(\n";
		exit(-1);
	}

	screen_ = SDL_SetVideoMode(width_, height_, 32, SDL_SWSURFACE);
	if (!screen_) {
		SDL_Quit();
		std::cerr << "SDL_SetVideoMode failed :(\n";
		exit(-1);
	}
	canvas_ = static_cast<uint32_t *>(screen_->pixels);

	SDL_WM_SetCaption(title_.c_str(), NULL);
}

void Window::render(const Scene &scene, const int &samples)
{
	const Camera &camera = scene.camera();
	const std::vector<Object *> &spheres = scene.objects();
	double inv = 1.0 / samples;
	Vector3d color;
	auto beg = std::chrono::high_resolution_clock::now();
	#pragma omp parallel for schedule(dynamic, 1) private(color)
	for (int x = 0; x < width_; ++x) {
		fprintf(stderr,"\rprogress: %5.2f%%", 100 * (x / static_cast<float>(width_-1)));
		for (int y = 0; y < height_; ++y) {
			for (int sx = 0, i = x + y * width_; sx < 2; ++sx) {
				for (int sy = 0; sy < 2; ++sy, color = Vector3d(0)) {
					for (int n = 0; n < samples; ++n) {
						double a = Random(), b = Random();
						Point2d sample((x+(a+sx+0.5)*0.5)/width_, (y+(b+sy+0.5)*0.5)/height_);
						Ray ray = camera.generateRay(sample);
						color += trace(ray, spheres, 0) * inv;
					}
					pixels_[i] += color * 0.25;
				}
			}
		}
	}

	auto end  = std::chrono::high_resolution_clock::now();
	auto Time = std::chrono::duration<double, std::ratio<1>>(end - beg).count();
	std::cout << "\ntime: " << std::setw(8) << Time << "  s\n";

	show();
	save_png();
}

void Window::show() const
{
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

void Window::save_ppm() const
{
	char file[32];
	strcpy(file, title_.c_str());
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

bool Window::save_png() const
{
	char file[32];
	strcpy(file, title_.c_str());
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
