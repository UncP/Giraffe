/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-06-27 13:10:53
**/

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

template <typename T>
class Vector2
{
	public:

		T x_, y_;

		Vector2():x_(0), y_(0) { }
		Vector2(const T &t):x_(t), y_(t) { }
		Vector2(const T &x, const T &y):x_(x), y_(y) { }
		Vector2(const Vector2<T> &v):x_(v.x_), y_(v.y_) { }
		Vector2<T>& operator=(const Vector2<T> &v) {
			x_ = v.x_;
			y_ = v.y_;
			return *this;
		}

		bool operator==(const Vector2<T> &v) const { return x_ == v.x_ && y_ == v.y_; }
		bool operator!=(const Vector2<T> &v) const { return !operator==(v); }

		Vector2<T> operator+(const Vector2<T> &v) const {
			return Vector2<T>(x_ + v.x_, y_ + v.y_);
		}
		Vector2<T>& operator+=(const Vector2<T> &v) {
			x_ += v.x_;
			y_ += v.y_;
			return *this;
		}
		Vector2<T> operator-(const Vector2<T> &v) const {
			return Vector2<T>(x_ - v.x_, y_ - v.y_);
		}
		Vector2<T>& operator-=(const Vector2<T> &v) {
			x_ -= v.x_;
			y_ -= v.y_;
			return *this;
		}

		template <typename U>
		Vector2<T> operator*(const U u) const {
			return Vector2<T>(x_ * u, y_ * u);
		}
		template <typename U>
		Vector2<T>& operator*=(const U u) {
			x_ *= u;
			y_ *= u;
			return *this;
		}
		template <typename U>
		Vector2<T> operator/(const U u) const {
			double inv = 1.0 / u;
			return Vector2<T>(x_ * inv, y_ * inv);
		}
		template <typename U>
		Vector2<T>& operator/=(const U u) {
			double inv = 1.0 / u;
			x_ *= inv;
			y_ *= inv;
			return *this;
		}

		Vector2<T> operator-() const { return Vector2<T>(-x_, -y_); }

		const T& operator[](const int i) const {
			assert(i >= 0 && i < 2);
			if (i == 0) return x_;
			return y_;
		}
		T& operator[](const int i) {
			assert(i >= 0 && i < 2);
			if (i == 0) return x_;
			return y_;
		}

		friend std::ostream& operator<<(std::ostream &os, const Vector2<T> &v) {
			return os << std::setw(8) << v.x_ << " "
								<< std::setw(8) << v.y_ << std::endl;
		}
};

typedef Vector2<double>		Vector2d;
typedef Vector2<float>		Vector2f;
typedef Vector2<int> 	 		Vector2i;

template <typename T>
class Vector3
{
	public:

		T x_, y_, z_;

		Vector3():x_(0), y_(0), z_(0) { }
		explicit Vector3(const T &t):x_(t), y_(t), z_(t) { }
		Vector3(const T &x, const T &y, const T &z):x_(x), y_(y), z_(z) { }
		Vector3(const Vector3<T> &v):x_(v.x_), y_(v.y_), z_(v.z_) { }
		Vector3<T>& operator=(const Vector3<T> &v) {
			x_ = v.x_;
			y_ = v.y_;
			z_ = v.z_;
			return *this;
		}

		bool operator==(const Vector3<T> &v) const {return x_ == v.x_ && y_ == v.y_ && z_ == v.z_;}
		bool operator!=(const Vector3<T> &v) const {return !operator==(v);}

		Vector3<T> operator+(const Vector3<T> &v) const {
			return Vector3<T>(x_ + v.x_, y_ + v.y_, z_ + v.z_);
		}
		Vector3<T> operator-(const Vector3<T> &v) const {
			return Vector3<T>(x_ - v.x_, y_ - v.y_, z_ - v.z_);
		}
		Vector3<T>& operator+=(const Vector3<T> &v) {
			x_ += v.x_, y_ += v.y_, z_ += v.z_;
			return *this;
		}
		Vector3<T>& operator-=(const Vector3<T> &v) {
			x_ -= v.x_, y_ -= v.y_, z_ -= v.z_;
			return *this;
		}

		template <typename U>
		Vector3<T> operator*(const U u) const {
			return Vector3<T>(x_ * u, y_ * u, z_ * u);
		}
		template <typename U>
		Vector3<T> operator/(const U u) const {
			double inv = 1.0 / u;
			return Vector3<T>(x_ * inv, y_ * inv, z_ * inv);
		}
		template <typename U>
		Vector3<T>& operator*=(const U u) {
			x_ *= u, y_ *= u, z_ *= u;
			return *this;
		}
		template <typename U>
		Vector3<T>& operator/=(const U u) {
			double inv = 1.0 / u;
			x_ *= inv, y_ *= inv, z_ *= inv;
			return *this;
		}

		Vector3<T> operator-() const { return Vector3<T>(-x_, -y_, -z_); }

		const T& operator[](const int i) const {
			assert(i >= 0 && i < 3);
			if (i == 0) return x_;
			if (i == 1) return y_;
			return z_;
		}
		T& operator[](const int i) {
			assert(i >= 0 && i < 3);
			if (i == 0) return x_;
			if (i == 1) return y_;
			return z_;
		}

		double length2() const { return x_ * x_ + y_ * y_ + z_ * z_; }
		double length () const { return std::sqrt(length2()); }

		friend std::ostream& operator<<(std::ostream &os, const Vector3<T> &v) {
			return os << std::setw(8) << v.x_ << " "
								<< std::setw(8) << v.y_ << " "
								<< std::setw(8) << v.z_ << std::endl;
		}
};

typedef Vector3<double> 			Vector3d;
typedef Vector3<float> 				Vector3f;
typedef Vector3<int> 					Vector3i;
typedef Vector3<unsigned int> Vector3u;
typedef Vector3<double> 			Color;

template <typename T, typename U>
inline Vector3<T> operator*(const U u, const Vector3<T> &v) {
	return v * u;
}

template <typename T>
inline double dot(const Vector3<T> &lhs, const Vector3<T> &rhs) {
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
inline Vector3<T> normalize(const Vector3<T> &v) {
	double len = v.length();
	assert(len);
	return v / len;
}

inline Color mult(const Color &a, const Color &b) {
	return Color(a.x_ * b.x_, a.y_ * b.y_, a.z_ * b.z_);
}

#endif /* _VECTOR_H_ */