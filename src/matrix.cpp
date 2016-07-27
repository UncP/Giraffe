/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-23 11:23:20
**/

#include "matrix.hpp"

Matrix Matrix::Identity(1, 0, 0, 0,
												0, 1, 0, 0,
												0, 0, 1, 0,
												0, 0, 0, 1
												);

Matrix::Matrix( double m00, double m10, double m20, double m30, \
								double m01, double m11, double m21, double m31, \
								double m02, double m12, double m22, double m32, \
								double m03, double m13, double m23, double m33)
{
	_m[0][0] = m00, _m[1][0] = m10, _m[2][0] = m20, _m[3][0] = m30,
	_m[0][1] = m01; _m[1][1] = m11, _m[2][1] = m21, _m[3][1] = m31,
	_m[0][2] = m02; _m[1][2] = m12, _m[2][2] = m22, _m[3][2] = m32,
	_m[0][3] = m03; _m[1][3] = m13, _m[2][3] = m23, _m[3][3] = m33;
}

Matrix Matrix::operator+(const Matrix &m) const
{
	Matrix M;
	for (size_t i = 0; i < 16; ++i)
		M.m_[i] = m_[i] + m.m_[i];
	return M;
}

Matrix Matrix::operator-(const Matrix &m) const
{
	Matrix M;
	for (size_t i = 0; i < 16; ++i)
		M.m_[i] = m_[i] - m.m_[i];
	return M;
}

Matrix& Matrix::operator+=(const Matrix &m)
{
	for (size_t i = 0; i < 16; ++i)
		m_[i] += m.m_[i];
	return *this;
}

Matrix& Matrix::operator-=(const Matrix &m)
{
	for (size_t i = 0; i < 16; ++i)
		m_[i] -= m.m_[i];
	return *this;
}

Matrix Matrix::operator*(const Matrix &m) const
{
	Matrix M;
	for (size_t i = 0; i < DIM_; ++i)
		for (size_t j = 0; j < DIM_; ++j)
			M._m[j][i] =  _m[0][i] * m._m[j][0] +
										_m[1][i] * m._m[j][1] +
										_m[2][i] * m._m[j][2] +
										_m[3][i] * m._m[j][3];
	return M;
}

Matrix& Matrix::operator*=(const Matrix &m)
{
	return *this = operator*(m);
}

Matrix& Matrix::makeTransform(const Vec3 &v)
{
	*this = Identity;
	_m[3][0] = v.x_;
	_m[3][1] = v.y_;
	_m[3][2] = v.z_;
	return *this;
}

Matrix& Matrix::makeRotateZ(const double angle)
{
	*this = Identity;
	const double c = cos(angle * (PI / 360.0));
	_m[0][0] = c;
	_m[1][1] = c;

	const double s = sin(angle * (PI / 360.0));
	_m[1][0] = -s;
	_m[0][1] =  s;

	return *this;
}

Matrix& Matrix::makeRotateY(const double angle)
{
	*this = Identity;
	const double c = cos(angle * (PI / 360.0));
	_m[0][0] = c;
	_m[2][2] = c;

	const double s = sin(angle * (PI / 360.0));

	_m[2][0] =  s;
	_m[0][2] = -s;

	return *this;
}

Matrix& Matrix::makeRotateX(const double angle)
{
	*this = Identity;
	const double c = cos(angle * (PI / 360.0));
	_m[1][1] = c;
	_m[2][2] = c;

	const double s = sin(angle * (PI / 360.0));
	_m[2][1] = -s;
	_m[1][2] =  s;

	return *this;
}

Matrix& Matrix::makeScale(const Vec3 &v)
{
	*this = Identity;
	_m[0][0] = v.x_;
	_m[1][1] = v.y_;
	_m[2][2] = v.z_;
	return *this;
}

Vec3 Matrix::operator*(const Vec3 &v) const
{
	// std::cout << v;
	double w =
		_m[0][3] * v.x_ + _m[1][3] * v.y_ + _m[2][3] * v.z_ + _m[3][3];
	// if (w == 0.0) w = -1.0;
	return Vec3(
		(_m[0][0] * v.x_ + _m[1][0] * v.y_ + _m[2][0] * v.z_ + _m[3][0])/w,
		(_m[0][1] * v.x_ + _m[1][1] * v.y_ + _m[2][1] * v.z_ + _m[3][1])/w,
		(_m[0][2] * v.x_ + _m[1][2] * v.y_ + _m[2][2] * v.z_ + _m[3][2])/w);
}

Matrix& Matrix::makeOrthographic(const Vec3 &lhs, const Vec3 &rhs)
{
	assert((lhs.x_ < rhs.x_) && (lhs.y_ < rhs.y_) && (lhs.z_ > rhs.z_));
	double r_l = rhs.x_ - lhs.x_;
	double t_b = rhs.y_ - lhs.y_;
	double n_f = lhs.z_ - rhs.z_;
	*this = Matrix(2 / r_l, 0, 0, -((lhs.x_ + rhs.x_) / r_l), \
									0, 2 / t_b, 0, -((lhs.y_ + rhs.y_) / t_b), \
									0, 0, 2 / n_f, -((lhs.z_ + rhs.z_) / n_f), \
									0, 0, 0, 1 \
								 );
	return *this;
}

Matrix& Matrix::makeProjection(const Vec3 &v)
{
	*this = Identity;
	_m[0][3] = v.x_;
	_m[1][3] = v.y_;
	_m[2][3] = v.z_;

	return *this;
}

Matrix& Matrix::makePerspective(const Vec3 &lhs, const Vec3 &rhs)
{
	assert((lhs.x_ < rhs.x_) && (lhs.y_ < rhs.y_) && (lhs.z_ > rhs.z_));
	double r_l = rhs.x_-lhs.x_;
	double t_b = rhs.y_-lhs.y_;
	double n_f = lhs.z_-rhs.z_;
	*this = Matrix(2*lhs.z_/r_l, 0, (lhs.x_ + rhs.x_)/-r_l, 0,
									0, 2*lhs.z_/t_b, (lhs.y_ + rhs.y_)/-t_b, 0,
									0, 0, (lhs.z_+rhs.z_)/n_f, 2*lhs.z_*rhs.z_/-n_f,
									0, 0, 1, 0
								);
	return *this;
}

/*
Matrix& Matrix::makePerspective(const double fov, const Vec2 &v)
{
	assert(v.x_ < v.y_);
	double ang = 1.0 / tan(fov * 0.5 * PI / 180.0);
	double n_f = v.x_ - v.y_;
	*this = Matrix(	ang, 0, 0, 0,
									0, ang, 0, 0,
									0, 0, v.y_ / n_f, -1,
									0, 0, v.y_ * v.x_ / n_f, 0);
	return *this;
}
*/
std::ostream& operator<<(std::ostream &os, const Matrix &m)
{
	os << "Matrix\n";
	for (size_t i = 0; i < Matrix::DIM_; ++i) {
		for (size_t j = 0; j < Matrix::DIM_; ++j)
			os << m._m[j][i] << " ";
		os << std::endl;
	}
	os << "Matrix\n";
	return os;
}
