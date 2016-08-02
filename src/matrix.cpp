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
	m_[0][0] = m00, m_[1][0] = m10, m_[2][0] = m20, m_[3][0] = m30,
	m_[0][1] = m01; m_[1][1] = m11, m_[2][1] = m21, m_[3][1] = m31,
	m_[0][2] = m02; m_[1][2] = m12, m_[2][2] = m22, m_[3][2] = m32,
	m_[0][3] = m03; m_[1][3] = m13, m_[2][3] = m23, m_[3][3] = m33;
}

Matrix Matrix::operator+(const Matrix &m) const
{
	Matrix M;
	for (size_t i = 0; i < 16; ++i)
		M._m[i] = _m[i] + m._m[i];
	return M;
}

Matrix Matrix::operator-(const Matrix &m) const
{
	Matrix M;
	for (size_t i = 0; i < 16; ++i)
		M._m[i] = _m[i] - m._m[i];
	return M;
}

Matrix& Matrix::operator+=(const Matrix &m)
{
	for (size_t i = 0; i < 16; ++i)
		_m[i] += m._m[i];
	return *this;
}

Matrix& Matrix::operator-=(const Matrix &m)
{
	for (size_t i = 0; i < 16; ++i)
		_m[i] -= m._m[i];
	return *this;
}

Matrix Matrix::operator*(const Matrix &m) const
{
	Matrix M;
	for (size_t i = 0; i < 4; ++i)
		for (size_t j = 0; j < 4; ++j)
			M.m_[j][i] =  m_[0][i] * m.m_[j][0] +
										m_[1][i] * m.m_[j][1] +
										m_[2][i] * m.m_[j][2] +
										m_[3][i] * m.m_[j][3];
	return M;
}

Matrix& Matrix::operator*=(const Matrix &m)
{
	return *this = operator*(m);
}

Matrix& Matrix::makeTranslate(const Vec &v)
{
	*this = Identity;
	m_[3][0] = v.x_;
	m_[3][1] = v.y_;
	m_[3][2] = v.z_;
	return *this;
}

Matrix& Matrix::makeRotateZ(const double angle)
{
	*this = Identity;
	const double c = cos(angle * (PI / 360.0));
	m_[0][0] = c;
	m_[1][1] = c;

	const double s = sin(angle * (PI / 360.0));
	m_[1][0] = -s;
	m_[0][1] =  s;

	return *this;
}

Matrix& Matrix::makeRotateY(const double angle)
{
	*this = Identity;
	const double c = cos(angle * (PI / 360.0));
	m_[0][0] = c;
	m_[2][2] = c;

	const double s = sin(angle * (PI / 360.0));

	m_[2][0] =  s;
	m_[0][2] = -s;

	return *this;
}

Matrix& Matrix::makeRotateX(const double angle)
{
	*this = Identity;
	const double c = cos(angle * (PI / 360.0));
	m_[1][1] = c;
	m_[2][2] = c;

	const double s = sin(angle * (PI / 360.0));
	m_[2][1] = -s;
	m_[1][2] =  s;

	return *this;
}

Matrix& Matrix::makeScale(const Vec &v)
{
	*this = Identity;
	m_[0][0] = v.x_;
	m_[1][1] = v.y_;
	m_[2][2] = v.z_;
	return *this;
}

Vec Matrix::operator*(const Vec &v) const
{
	double w = m_[0][3] * v.x_ + m_[1][3] * v.y_ + m_[2][3] * v.z_ + m_[3][3];
	return Vec(
		(m_[0][0] * v.x_ + m_[1][0] * v.y_ + m_[2][0] * v.z_ + m_[3][0])/w,
		(m_[0][1] * v.x_ + m_[1][1] * v.y_ + m_[2][1] * v.z_ + m_[3][1])/w,
		(m_[0][2] * v.x_ + m_[1][2] * v.y_ + m_[2][2] * v.z_ + m_[3][2])/w);
}

Matrix& Matrix::toRaster(const int width, const int height)
{
	*this = Matrix(width / 2 , 		0, 			0, (width - 1) / 2,
										0, 		 -height / 2, 0, (height - 1) / 2,
										0, 					0, 			1, 				0,
										0, 					0, 			0, 				1);
	return *this;
}

Matrix& Matrix::toNdc(const Vec &lhs, const Vec &rhs)
{
	assert((lhs.x_ < rhs.x_) && (lhs.y_ < rhs.y_) && (lhs.z_ > rhs.z_));
	double r_l = rhs.x_ - lhs.x_;
	double t_b = rhs.y_ - lhs.y_;
	double n_f = lhs.z_ - rhs.z_;
	*this = Matrix(2 / r_l, 		0, 			0,       -((lhs.x_ + rhs.x_) / r_l), \
										0, 		 2 / t_b, 	0,       -((lhs.y_ + rhs.y_) / t_b), \
										0, 				0, 		 2 / n_f,  -((lhs.z_ + rhs.z_) / n_f), \
										0, 				0, 			0, 															1);
	return *this;
}

Matrix& Matrix::makeProjection(const Vec &v)
{
	*this = Identity;
	m_[0][3] = v.x_;
	m_[1][3] = v.y_;
	m_[2][3] = v.z_;

	return *this;
}

Matrix& Matrix::makePerspective(const Vec &lhs, const Vec &rhs)
{
	assert((lhs.x_ < rhs.x_) && (lhs.y_ < rhs.y_) && (lhs.z_ < rhs.z_));
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

Matrix& Matrix::makePerspective(const double fov, const double near, const double far)
{
	assert(near < far);
	double ang = 1.0 / tan(fov * PI / 360.0);
	double n_f = near - far;
	*this = Matrix(	ang,  0, 		0, 								 0,
									0, 	  ang,  0,			 			     0,
									0,    0, 	  far / n_f,        -1,
									0,    0,   	far * near / n_f,  0);
	return *this;
}

Matrix inverse(Matrix &m)
{
	double inv[16];

	inv[0] = 	m._m[5]  * m._m[10] * m._m[15] -
						m._m[5]  * m._m[11] * m._m[14] -
						m._m[9]  * m._m[6]  * m._m[15] +
						m._m[9]  * m._m[7]  * m._m[14] +
						m._m[13] * m._m[6]  * m._m[11] -
						m._m[13] * m._m[7]  * m._m[10];

	inv[4] = -m._m[4]  * m._m[10] * m._m[15] +
						m._m[4]  * m._m[11] * m._m[14] +
						m._m[8]  * m._m[6]  * m._m[15] -
						m._m[8]  * m._m[7]  * m._m[14] -
						m._m[12] * m._m[6]  * m._m[11] +
						m._m[12] * m._m[7]  * m._m[10];

	inv[8] = 	m._m[4]  * m._m[9]  * m._m[15] -
						m._m[4]  * m._m[11] * m._m[13] -
						m._m[8]  * m._m[5]  * m._m[15] +
						m._m[8]  * m._m[7]  * m._m[13] +
						m._m[12] * m._m[5]  * m._m[11] -
						m._m[12] * m._m[7]  * m._m[9];

	inv[12] = -m._m[4]  * m._m[9]  * m._m[14] +
						 m._m[4]  * m._m[10] * m._m[13] +
						 m._m[8]  * m._m[5]  * m._m[14] -
						 m._m[8]  * m._m[6]  * m._m[13] -
						 m._m[12] * m._m[5]  * m._m[10] +
						 m._m[12] * m._m[6]  * m._m[9];

	inv[1] = -m._m[1]  * m._m[10] * m._m[15] +
						m._m[1]  * m._m[11] * m._m[14] +
						m._m[9]  * m._m[2] *  m._m[15] -
						m._m[9]  * m._m[3] *  m._m[14] -
						m._m[13] * m._m[2] *  m._m[11] +
						m._m[13] * m._m[3] *  m._m[10];

	inv[5] =  m._m[0]  * m._m[10] * m._m[15] -
						m._m[0]  * m._m[11] * m._m[14] -
						m._m[8]  * m._m[2]  * m._m[15] +
						m._m[8]  * m._m[3]  * m._m[14] +
						m._m[12] * m._m[2]  * m._m[11] -
						m._m[12] * m._m[3]  * m._m[10];

	inv[9] = -m._m[0]  * m._m[9]  * m._m[15] +
						m._m[0]  * m._m[11] * m._m[13] +
						m._m[8]  * m._m[1]  * m._m[15] -
						m._m[8]  * m._m[3]  * m._m[13] -
						m._m[12] * m._m[1]  * m._m[11] +
						m._m[12] * m._m[3]  * m._m[9];

	inv[13] = m._m[0]  * m._m[9]  * m._m[14] -
						m._m[0]  * m._m[10] * m._m[13] -
						m._m[8]  * m._m[1]  * m._m[14] +
						m._m[8]  * m._m[2]  * m._m[13] +
						m._m[12] * m._m[1]  * m._m[10] -
						m._m[12] * m._m[2]  * m._m[9];

	inv[2] = m._m[1]  * m._m[6] * m._m[15] -
					 m._m[1]  * m._m[7] * m._m[14] -
					 m._m[5]  * m._m[2] * m._m[15] +
					 m._m[5]  * m._m[3] * m._m[14] +
					 m._m[13] * m._m[2] * m._m[7] -
					 m._m[13] * m._m[3] * m._m[6];

	inv[6] = -m._m[0]  * m._m[6] * m._m[15] +
						m._m[0]  * m._m[7] * m._m[14] +
						m._m[4]  * m._m[2] * m._m[15] -
						m._m[4]  * m._m[3] * m._m[14] -
						m._m[12] * m._m[2] * m._m[7] +
						m._m[12] * m._m[3] * m._m[6];

	inv[10] = m._m[0]  * m._m[5] * m._m[15] -
						m._m[0]  * m._m[7] * m._m[13] -
						m._m[4]  * m._m[1] * m._m[15] +
						m._m[4]  * m._m[3] * m._m[13] +
						m._m[12] * m._m[1] * m._m[7] -
						m._m[12] * m._m[3] * m._m[5];

	inv[14] = -m._m[0]  * m._m[5] * m._m[14] +
						 m._m[0]  * m._m[6] * m._m[13] +
						 m._m[4]  * m._m[1] * m._m[14] -
						 m._m[4]  * m._m[2] * m._m[13] -
						 m._m[12] * m._m[1] * m._m[6] +
						 m._m[12] * m._m[2] * m._m[5];

	inv[3] = -m._m[1] * m._m[6] * m._m[11] +
						m._m[1] * m._m[7] * m._m[10] +
						m._m[5] * m._m[2] * m._m[11] -
						m._m[5] * m._m[3] * m._m[10] -
						m._m[9] * m._m[2] * m._m[7] +
						m._m[9] * m._m[3] * m._m[6];

	inv[7] =  m._m[0] * m._m[6] * m._m[11] -
						m._m[0] * m._m[7] * m._m[10] -
						m._m[4] * m._m[2] * m._m[11] +
						m._m[4] * m._m[3] * m._m[10] +
						m._m[8] * m._m[2] * m._m[7] -
						m._m[8] * m._m[3] * m._m[6];

	inv[11] = -m._m[0] * m._m[5] * m._m[11] +
						 m._m[0] * m._m[7] * m._m[9] +
						 m._m[4] * m._m[1] * m._m[11] -
						 m._m[4] * m._m[3] * m._m[9] -
						 m._m[8] * m._m[1] * m._m[7] +
						 m._m[8] * m._m[3] * m._m[5];

	inv[15] = m._m[0] * m._m[5] * m._m[10] -
	    			m._m[0] * m._m[6] * m._m[9] -
	    			m._m[4] * m._m[1] * m._m[10] +
	    			m._m[4] * m._m[2] * m._m[9] +
	    			m._m[8] * m._m[1] * m._m[6] -
	    			m._m[8] * m._m[2] * m._m[5];

	double det = m._m[0] * inv[0] + m._m[1] * inv[4] + m._m[2] * inv[8] + m._m[3] * inv[12];

	if (det == 0) { return Matrix::Identity; }

	Matrix ret;
	det = 1.0 / det;
	for (int i = 0; i < 16; ++i)
		ret._m[i] = inv[i] * det;
	return ret;
}

Matrix translate(const Vec &v)
{
	return Matrix(1, 0, 0, v[0], 0, 1, 0, v[1], 0, 0, 1, v[2], 0, 0, 0, 1);
}

Matrix scale(const Vec &v)
{
	return Matrix(v[0], 0, 0, 0, 0, v[1], 0, 0, 0, 0, v[2], 0, 0, 0, 0, 1);
}

std::ostream& operator<<(std::ostream &os, const Matrix &m)
{
	os << "Matrix\n";
	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j)
			os << std::setw(12) << m.m_[j][i];
		os << std::endl;
	}
	os << "Matrix\n";
	return os;
}
