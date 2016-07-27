/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-22 19:42:57
**/

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdlib>

#include "vector.hpp"

class Matrix
{
	friend
		std::ostream& operator<<(std::ostream &, const Matrix &);
	public:
		static const int DIM_ = 4;
		static Matrix Identity;

		Matrix() = default;
		Matrix(	double m00, double m10, double m20, double m30, \
						double m01, double m11, double m21, double m31, \
						double m02, double m12, double m22, double m32, \
						double m03, double m13, double m23, double m33  \
		);

		Matrix& operator=(const Matrix &m) {
			static const int size = DIM_ * DIM_ * sizeof(double);
			memcpy(_m, m._m, size);
			return *this;
		}

		Matrix operator+(const Matrix &) const;
		Matrix operator-(const Matrix &) const;
		Matrix& operator+=(const Matrix &);
		Matrix& operator-=(const Matrix &);
		Matrix operator*(const Matrix &) const;
		Matrix& operator*=(const Matrix &);

		Matrix& makeScale(const Vec3 &);
		Matrix& makeRotateX(const double);
		Matrix& makeRotateY(const double);
		Matrix& makeRotateZ(const double);
		Matrix& makeTransform(const Vec3 &);

		Vec3 operator*(const Vec3 &) const;

		Matrix& makeOrthographic(const Vec3 &, const Vec3 &);
		Matrix& makeProjection(const Vec3 &);

		Matrix& makePerspective(const Vec3 &, const Vec3 &);
		// Matrix& makePerspective(const double, const Vec2 &);

		~Matrix() { }
	private:
		union {
			double m_[DIM_ * DIM_];
			double _m[DIM_][DIM_];
		};
};

#endif /* _MATRIX_H_ */