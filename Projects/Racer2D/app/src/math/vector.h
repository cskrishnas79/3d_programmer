//------------------------------------------------------------------
//
// Vector class Declaration
//
//------------------------------------------------------------------
#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

class Vector
{
public:
	Vector(double val[3]);
	Vector(double x, double y, double z);
	~Vector();

	Vector(const Vector& v);              // copy constructor
	Vector& operator=(const Vector& v);   // assignment operator

	Vector normalize() const;
	Vector operator+(const Vector& v);
	Vector operator-(const Vector& v);
	Vector operator*(const double& scalar);

	double angle(const Vector& v) const;
	double length() const;
	double dot(const Vector& v) const;
	Vector cross(const Vector& v) const;
	const double* get() const { return m_val; }

private:
	double m_val[3];
};
#endif // VECTOR_H
//------------------------------------------------------------------