/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-27 13:10:53
**/

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <iomanip>
#include <cmath>

using std::setw;

/**
 *		VECTOR2
**/
template <typename T>
class Vector2
{
	public:
		union { T x_; T u_; };
		union { T y_; T v_; };

		// Constructor
		Vector2() = default;
		Vector2(const T &t):x_(t), y_(t) { }
		Vector2(const T &x, const T &y):x_(x), y_(y) { }
		Vector2(const Vector2 &v):x_(v.x_), y_(v.y_) { }

		Vector2& operator=(const Vector2 &v) {
			x_ = v.x_;
			y_ = v.y_;
			return *this;
		}

		// Operation

		~Vector2() { }
};

typedef Vector2<double> Vec2;

template <typename T>
std::ostream& operator<<(std::ostream &os, const Vector2<T> &v) {
	return os << setw(6) << v.x_ << " " << setw(6) << v.y_ << std::endl;
}


/**
 *		VECTOR3
**/
template <typename T>
class Vector3
{
	public:
		static Vector3<double> Zero;
		static Vector3<double> One;

		union { T x_; T r_; };
		union { T y_; T g_; };
		union { T z_; T b_; };

		Vector3() = default;
		Vector3(const T &t):x_(t), y_(t), z_(t) { }
		Vector3(const T &x, const T &y, const T &z):x_(x), y_(y), z_(z) { }
		Vector3(const Vector3 &v):x_(v.x_), y_(v.y_), z_(v.z_) { }

		Vector3& operator=(const Vector3 &v) {
			x_ = v.x_;
			y_ = v.y_;
			z_ = v.z_;
			return *this;
		}

		const bool operator==(const Vector3 &v) const {
			return x_ == v.x_ && y_ == v.y_ && z_ == v.z_;
		}
		const bool operator!=(const Vector3 &v) const {
			return !operator==(v);
		}

		Vector3 operator+(const Vector3 &v) const {
			return Vector3(x_ + v.x_, y_ + v.y_, z_ + v.z_);
		}
		Vector3 operator-(const Vector3 &v) const {
			return Vector3(x_ - v.x_, y_ - v.y_, z_ - v.z_);
		}
		Vector3& operator+=(const Vector3 &v) {
			x_ += v.x_, y_ += v.y_, z_ += v.z_;
			return *this;
		}
		Vector3& operator-=(const Vector3 &v) {
			x_ -= v.x_, y_ -= v.y_, z_ -= v.z_;
			return *this;
		}

		Vector3 operator*(const double d) const {
			return Vector3(x_ * d, y_ * d, z_ * d);
		}
		Vector3 operator/(const double d) const {
			const double inv = 1.0 / d;
			return Vector3(x_ * inv, y_ * inv, z_ * inv);
		}
		Vector3& operator*=(const double d) {
			x_ *= d, y_ *= d, z_ *= d;
			return *this;
		}
		Vector3& operator/=(const double d) {
			const double inv = 1.0 / d;
			x_ *= inv, y_ *= inv, z_ *= inv;
			return *this;
		}
		Vector3 operator-() const {
			return Vector3(-x_, -y_, -z_);
		}

		const double length2() const {
			return x_ * x_ + y_ * y_ + z_ * z_;
		}
		const double length() const {
			return sqrt(length2());
		}

		~Vector3() { }
};

typedef Vector3<double> Vec3;

template <typename T>
inline Vector3<T> operator*(const double d, const Vector3<T> &v) {
	return v * d;
}

template <typename T>
inline const double dot(const Vector3<T> &lhs, const Vector3<T> &rhs) {
	return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_ + lhs.z_ * rhs.z_;
}

template <typename T>
inline Vector3<T> cross(const Vector3<T> &lhs, const Vector3<T> &rhs) {
	return Vector3<T>(
		lhs.y_ * rhs.z_ - lhs.z_ * rhs.y_,
		lhs.z_ * rhs.x_ - lhs.x_ * rhs.z_,
		lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_
	);
}

template <typename T>
inline void normalize(Vector3<T> &v) {
	double inv = 1.0 / v.length();
	v *= inv;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const Vector3<T> &v) {
	return os << setw(6) << v.x_ << " " << setw(6) << v.y_ << " " << setw(6) << v.z_ << std::endl;
}

/**
 *		COLOR
**/
class Color : public Vec3
{
	public:
		static Color Black;
		static Color White;
		static Color Red;
		static Color Green;
		static Color Blue;
		static Color Yellow;
		static Color Purple;

		double a_ = 1.0;

		Color() = default;
		Color(const double &d):Vec3(d) { }
		Color(const double &r, const double &g, const double &b):Vec3(r, g, b) { }
		Color(const Vec3 &c):Vec3(c) { }

		uint32_t uint() const {
			uint32_t ret = 0;
			ret |= static_cast<uint8_t>((a_ > 1.0 ? 1.0 : a_) * 255.0) << 24;
			ret |= static_cast<uint8_t>((x_ > 1.0 ? 1.0 : x_) * 255.0) << 16;
			ret |= static_cast<uint8_t>((y_ > 1.0 ? 1.0 : y_) * 255.0) <<  8;
			ret |= static_cast<uint8_t>((z_ > 1.0 ? 1.0 : z_) * 255.0);
			return ret;
		}

		~Color() { };
};

#endif /* _VECTOR_H_ */