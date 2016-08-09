/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:	  https://www.github.com/UncP
 *    > Description:
 *
 *    > Created Time: 2016-08-08 15:25:05
**/

#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <iostream>
#include <iomanip>
#include <cassert>

#include "vector.hpp"

template <typename T>
class Point2
{
	public:
		T x_;
		T y_;

		Point2(const T &t):x_(t), y_(t) { }
		Point2(const T &x, const T &y):x_(x), y_(y) { }
		Point2(const Point2<T> &p):x_(p.x_), y_(p.y_) { }
		Point2<T>& operator=(const Point2<T> &p) {
			x_ = p.x_;
			y_ = p.y_;
			return *this;
		}

		bool operator==(const Point2<T> &p) { return x_ == p.x_ && y_ == p.y_; }
		bool operator!=(const Point2<T> &p) { return !operator==(p); }

		Point2<T> operator+(const Point2<T> &p) const {
			return Point2<T>(x_ + p.x_, y_ + p.y_);
		}
		Point2<T>& operator+=(const Point2<T> &p) {
			x_ += p.x_;
			y_ += p.y_;
			return *this;
		}
		Point2<T> operator-(const Point2<T> &p) const {
			return Point2<T>(x_ - p.x_, y_ - p.y_);
		}
		Point2<T>& operator-=(const Point2<T> &p) {
			x_ -= p.x_;
			y_ -= p.y_;
			return *this;
		}

		template <typename U>
		Point2<T> operator*(const U u) const {
			return Point2<T>(x_ * u, y_ * u);
		}
		template <typename U>
		Point2<T>& operator*=(const U u) {
			x_ *= u;
			y_ *= u;
			return *this;
		}
		template <typename U>
		Point2<T> operator/(const U u) const {
			double inv = 1.0 / u;
			return Point2<T>(x_ * inv, y_ * inv);
		}
		template <typename U>
		Point2<T>& operator/=(const U u) {
			double inv = 1.0 / u;
			x_ *= inv;
			y_ *= inv;
			return *this;
		}

		Point2<T> operator-() const { return Point2<T>(-x_, -y_); }

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

		friend std::ostream& operator<<(std::ostream &os, const Point2<T> &p) {
			return os << std::setw(8) << p.x_ << " "
								<< std::setw(8) << p.y_ << std::endl;
		}
};

typedef Point2<double>	Point2d;
typedef Point2<float>		Point2f;
typedef Point2<int> 		Point2i;

template <typename T>
class Point3
{
	public:

		T x_, y_, z_;

		Point3():x_(0), y_(0), z_(0) { }
		Point3(const T &t):x_(t), y_(t), z_(t) { }
		Point3(const T &x, const T &y, const T &z):x_(x), y_(y), z_(z) { }
		Point3(const Point3<T> &p):x_(p.x_), y_(p.y_), z_(p.z_) { }
		Point3& operator=(const Point3<T> &p) {
			x_ = p.x_;
			y_ = p.y_;
			z_ = p.z_;
			return *this;
		}

		template <typename U>
		Point3(const Vector3<U> &v):x_(v.x_), y_(v.y_), z_(v.z_) { }

		template <typename U>
		explicit operator Vector3<U>() const {
			return Vector3<U>(x_, y_, z_);
		}
		bool operator==(const Point3<T> &p) const { return x_ == p.x_ && y_ == p.y_ && z_ == p.z_; }
		bool operator!=(const Point3<T> &p) const { return !operator==(p); }

		Point3<T> operator+(const Point3<T> &p) const {
			return Point3<T>(x_ + p.x_, y_ + p.y_, z_ + p.z_);
		}
		Point3<T> operator+(const Vector3<T> &v) const {
			return Point3<T>(x_ + v.x_, y_ + v.y_, z_ + v.z_);
		}
		Point3<T>& operator+=(const Point3<T> &p) {
			x_ += p.x_;
			y_ += p.y_;
			z_ += p.z_;
			return *this;
		}
		Point3<T>& operator+=(const Vector3<T> &v) {
			x_ += v.x_;
			y_ += v.y_;
			z_ += v.z_;
			return *this;
		}
		Vector3<T> operator-(const Point3<T> &p) const {
			return Vector3<T>(x_ - p.x_, y_ - p.y_, z_ - p.z_);
		}
		Point3<T> operator-(const Vector3<T> &v) const {
			return Point3<T>(x_ - v.x_, y_ - v.y_, z_ - v.z_);
		}
		Point3<T>& operator-=(const Point3<T> &p) {
			x_ -= p.x_;
			y_ -= p.y_;
			z_ -= p.z_;
			return *this;
		}
		Point3<T>& operator-=(const Vector3<T> &v) {
			x_ -= v.x_;
			y_ -= v.y_;
			z_ -= v.z_;
			return *this;
		}

		template <typename U>
		Point3<T> operator*(const U u) const {
			return Point3<T>(x_ * u, y_ * u, z_ * u);
		}
		template <typename U>
		Point3<T>& operator*=(const U u) {
			x_ *= u;
			y_ *= u;
			z_ *= u;
			return *this;
		}
		template <typename U>
		Point3<T> operator/(const U u) const {
			double inv = 1.0 / u;
			return Point3<T>(x_ * inv, y_ * inv, z_ * inv);
		}
		template <typename U>
		Point3<T>& operator/=(const U u) {
			double inv = 1.0 / u;
			x_ *= inv;
			y_ *= inv;
			z_ *= inv;
			return *this;
		}

		Point3<T> operator-() const { return Point3<T>(-x_, -y_, -z_); }

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

		bool operator<(const Point3<T> &p) const {
			if (x_ == p.x_) {
				if (y_ == p.y_) {
					return z_ < p.z_;
				} else {
					return y_ < p.y_;
				}
			} else {
				return x_ < p.x_;
			}
		}

		friend std::ostream& operator<<(std::ostream &os, const Point3<T> &p) {
			return os << std::setw(8) << p.x_ << " "
								<< std::setw(8) << p.y_ << " "
								<< std::setw(8) << p.z_ << std::endl;
		}
};

typedef Point3<double>					Point3d;
typedef Point3<float> 					Point3f;
typedef Point3<int> 						Point3i;
typedef Point3<unsigned int> 		Point3u;

template <typename T>
inline double proj(const Point3<T> &p, const Vector3<T> &v) {
	return p.x_ * v.x_ + p.y_ * v.y_ + p.z_ * v.z_;
}

#endif /* _POINT_HPP_ */