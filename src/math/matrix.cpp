/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Giraffe
 *    > Description:
 *
 *    > Created Time: 2016-06-23 11:23:20
**/

#include "matrix.hpp"

namespace Giraffe {

Matrix Matrix::Identity(1, 0, 0, 0,
												0, 1, 0, 0,
												0, 0, 1, 0,
												0, 0, 0, 1);

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

Matrix inverse(const Matrix &m)
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

Matrix perspective(const double angle, const double n, const double f)
{
	double fov = 1.0 / std::tan(radian(angle) * 0.5);
	double n_f = n - f;

	return Matrix(fov, 	0, 		0,				0,
								0, 	 fov,		0,		 		0,
								0, 		0, 	f/n_f,     -1,
								0, 		0, 	(f*n)/n_f,  0);
}

Matrix transform(const Vector3d &v)
{
	return Matrix(1, 0, 0, v[0],
								0, 1, 0, v[1],
								0, 0, 1, v[2],
								0, 0, 0, 1);
}

Matrix scale(const double x, const double y, const double z)
{
	return Matrix(x, 0, 0, 0,
								0, y, 0, 0,
								0, 0, z, 0,
								0, 0, 0, 1);
}

Matrix rotateX(const double angle)
{
	double c = std::cos(radian(angle));
	double s = std::sin(radian(angle));

	return Matrix(1, 0,  0, 0,
								0, c, -s, 0,
							  0, s,  c, 0,
								0, 0,  0, 1);
}

Matrix rotateY(const double angle)
{
	double c = std::cos(radian(angle));
	double s = std::sin(radian(angle));
	return Matrix(c, 0, s, 0,
								0, 1, 0, 0,
							 -s, 0, c, 0,
								0, 0, 0, 1);
}

Matrix rotateZ(const double angle)
{
	double c = std::cos(radian(angle));
	double s = std::sin(radian(angle));
	return Matrix(c, -s, 0, 0,
								s,  c, 0, 0,
								0,  0, 1, 0,
								0,  0, 0, 1);
}

} // namespace Giraffe
