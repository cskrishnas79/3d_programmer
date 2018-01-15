//------------------------------------------------------------------
//
// Matrix class Implementation
//
//------------------------------------------------------------------
#include "math\matrix.h"

Matrix::Matrix()
{
	m_val[0] = m_val[5] = m_val[10] = m_val[15] = 1.0f;
	m_val[1] = m_val[2] = m_val[3] = m_val[4] = m_val[6] \
	= m_val[7] = m_val[8] = m_val[9] = m_val[11] = m_val[12] \
	= m_val[13] = m_val[14] = 0.0f;
}

Matrix::Matrix(double val[16])
{
	for (int i = 0; i < 16; ++i)
		m_val[i] = val[i];
}

Matrix::~Matrix()
{
}

void Matrix::translate(double transX, double transY, double transZ)
{
	m_val[12] += m_val[15] * transX;
	m_val[13] += m_val[15] * transY;
	m_val[14] += m_val[15] * transZ;
}

void Matrix::rotateX(double rotAngle)
{
	/*
	[1		0			0		0]
	[0 cos(Angle) -sin(Angle)	0]
	[0 sin(Angle) cos(Angle)	0]
	[0		0			0		1]
	*/
	double c = cos(rotAngle);
	double s = sin(rotAngle);
	m_val[0] = m_val[15] = 1.0;
	m_val[1] = m_val[2] = m_val[3] = m_val[4] = 0.0;
	m_val[5] = c;
	m_val[6] = s;
	m_val[7] = m_val[8] = 0.0;
	m_val[9] = -s;
	m_val[10] = c;
	m_val[11] = m_val[12] = m_val[13] = m_val[14] = 0.0;
}

void Matrix::rotateY(double rotAngle)
{
	/*
	[cos(Angle) 0 sin(Angle)	0]
	[0			1	0			0]
	[-sin(Angle)0 cos(Angle)	0]
	[0			0	0			1]
	*/
	double c = cos(rotAngle);
	double s = sin(rotAngle);
	m_val[0] = c;
	m_val[1] = m_val[3] = m_val[4] = 0.0;
	m_val[2] = -s;
	m_val[5] = m_val[15] = 1.0;
	m_val[6] = m_val[7] = m_val[9] = 0.0;
	m_val[8] = s;
	m_val[10] = c;
	m_val[11] = m_val[12] = m_val[13] = m_val[14] = 0.0;
}

void Matrix::rotateZ(double rotAngle)
{
	/*
	[cos(Angle) -sin(Angle) 0 0]
	[sin(Angle) cos(Angle)  0 0]
	[0				0		1 0]
	[0				0		0 1]
	*/
	double c = cos(rotAngle);
	double s = sin(rotAngle);
	m_val[0] = c;
	m_val[1] = s;
	m_val[2] = m_val[3] = 0.0;
	m_val[4] = -s;
	m_val[5] = c;
	m_val[6] = m_val[7] = m_val[8] = m_val[9] = 0.0;
	m_val[10] = m_val[15] = 1.0;
	m_val[11] = m_val[12] = m_val[13] = m_val[14] = 0.0;
}

void Matrix::operator*(double val[3]) const
{
	double nVal[3] = { 0.0,0.0,0.0 };
	nVal[0] = m_val[0] * val[0] + m_val[4] * val[1] + m_val[8] * val[2] + m_val[12];
	nVal[1] = m_val[1] * val[0] + m_val[5] * val[1] + m_val[9] * val[2] + m_val[13];
	nVal[2] = m_val[2] * val[0] + m_val[6] * val[1] + m_val[10] * val[2] + m_val[14];

	val[0] = nVal[0]; val[1] = nVal[1]; val[2] = nVal[2];
}

Matrix Matrix::operator*(const Matrix& mat) const
{
	const double* val = mat.get();
	double nVal[16] = { 0.0 };

	for (int i = 0; i < 4; ++i) // row
	{
		for (int j = 0; j < 4; ++j) // column
		{
			double value = 0.0;
			for (int k = 0; k < 4; ++k)
			{
				value += val[i + k * 4] * m_val[k + j * 4];
			}

			nVal[j * 4 + i] = value;
		}
	}

	Matrix update(nVal);
	return update;
}

Matrix& Matrix::operator*=(const Matrix& mat)
{
	*this = (*this)*mat;
	return (*this);
}