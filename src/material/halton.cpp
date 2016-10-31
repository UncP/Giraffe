/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-10-31 12:06:04
**/

#include <mutex>

#include "halton.hpp"

namespace Giraffe {

class HaltonImpl
{
	public:
		HaltonImpl(int num1, int num2) {
			double factor = base_ = 1.0 / num2;
			value_ = 0.0;
			for (; num1 > 0; ) {
				value_ += factor * static_cast<double>(num1 % num2);
				num1 /= num2;
				factor *= base_;
			}
		}

		double next()
		{
			std::lock_guard<std::mutex> lock(mutex_);
			double r = 1.0 - value_ - 0.0000001;
			if(base_ < r) value_ += base_;
			else {
				double h = base_, hh;
				do {
					hh = h;
					h *= base_;
				} while (h >= r);
				value_ += hh + h - 1.0;
			}
			return value_;
		}

	private:
		std::mutex mutex_;
		double value_;
		double base_;
};

static HaltonImpl hal1(0, 2);
static HaltonImpl hal2(0, 2);

Color Halton::sample(const Vector3d &out, Vector3d &in, const Vector3d &normal, double &pdf)
{
	double u1 = hal1.next(), u2 = hal2.next();

	double r = std::sqrt(1.0 - u1 * u1);
	double phi = DOU_PI * u2;

	in = normalize(normal + Vector3d(std::cos(phi) * r, std::sin(phi) * r, u1));
	return color_;
}

} // namespace Giraffe
