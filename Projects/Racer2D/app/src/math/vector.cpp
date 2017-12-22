//------------------------------------------------------------------
//
// Vector class Implementation
//
//------------------------------------------------------------------
#include "math\vector.h"

Vector::Vector(double val[3])
{
	m_val[0] = val[0];	m_val[1] = val[1];	m_val[2] = val[2];
}

Vector::Vector(double x, double y, double z)
{
	m_val[0] = x;	m_val[1] = y;	m_val[2] = z;
}

Vector::~Vector()
{
}

Vector::Vector(const Vector& v)
{
	m_val[0] = v.m_val[0];
	m_val[1] = v.m_val[1];
	m_val[2] = v.m_val[2];
}

Vector& Vector::operator=(const Vector& v)
{
	m_val[0] = v.m_val[0];
	m_val[1] = v.m_val[1];
	m_val[2] = v.m_val[2];
	return (*this);
}

double Vector::length() const
{
	double val = (m_val[0] * m_val[0] + m_val[1] * m_val[1] + m_val[2] * m_val[2]);
	return sqrt(val);
}

Vector Vector::normalize() const
{
	double len = length();
	double val[3] = { 0.0 };
	val[0] = m_val[0] / len;
	val[1] = m_val[1] / len;
	val[2] = m_val[2] / len;
	return Vector(val);
}

double Vector::angle(const Vector& v) const
{
	double dot = this->dot(v);
	double l1 = length();
	double l2 = v.length();
	double ratio = dot / (l1*l2);
	double angle = acos(ratio);
	return angle;
}

Vector Vector::operator+(const Vector& v)
{
	double val[3] = { 0.0 };
	val[0] = m_val[0] + v.m_val[0];
	val[1] = m_val[1] + v.m_val[1];
	val[2] = m_val[2] + v.m_val[2];
	return Vector(val);
}

Vector Vector::operator-(const Vector& v)
{
	double val[3] = { 0.0 };
	val[0] = m_val[0] - v.m_val[0];
	val[1] = m_val[1] - v.m_val[1];
	val[2] = m_val[2] - v.m_val[2];
	return Vector(val);
}

Vector Vector::operator*(const double& scalar)
{
	double val[3] = { 0.0 };
	val[0] = m_val[0] * scalar;
	val[1] = m_val[1] * scalar;
	val[2] = m_val[2] * scalar;
	return Vector(val);
}

double Vector::dot(const Vector& v) const
{
	double val = (m_val[0] * v.m_val[0] + m_val[1] * v.m_val[1] + m_val[2] * v.m_val[2]);
	return val;
}

Vector Vector::cross(const Vector& v) const
{
	double val[3] = { 0.0 };
	val[0] = m_val[1] * v.m_val[2] - m_val[2] * v.m_val[1];
	val[1] = m_val[2] * v.m_val[0] - m_val[0] * v.m_val[2];
	val[2] = m_val[0] * v.m_val[1] - m_val[1] * v.m_val[0];
	return Vector(val);
}