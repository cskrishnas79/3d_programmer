//------------------------------------------------------------------
//
// Matrix class Declaration
//
//------------------------------------------------------------------
#ifndef MATRIX_H
#define MATRIX_H

#include "math\vector.h"

class Matrix
{
public:
	Matrix();
	Matrix(double val[16]);
	~Matrix();

	// Translation in x, y and z direction respectively
	void translate(double transX, double transY, double transZ);
	// Rotation angle in radian about axis respectively
	void rotateX(double rotAngle);
	void rotateY(double rotAngle);
	void rotateZ(double rotAngle);
	const double* get() const { return m_val; }

	void operator*(double val[3]) const;
	Matrix operator*(const Matrix& mat) const;
	Matrix& operator*=(const Matrix& mat);

private:
	double m_val[16]; // column major as per opengl
};
#endif // MATRIX_H
//------------------------------------------------------------------