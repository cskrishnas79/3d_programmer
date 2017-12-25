//------------------------------------------------------------------
//
// GL Object to draw
//
//------------------------------------------------------------------
#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include "data\data.h"
#include "data\geom.h"
#include "data\topo.h"
#include "data\display.h"
#include "freeglut\include\freeglut.h" // thirdpty library interface

class GLObject
{
public:
	GLObject(GLenum mode);
	~GLObject();

	bool Point(const std::shared_ptr<data::Geom>& pGeom);
	bool Line(const std::shared_ptr<data::Geom>& pGeom);
	bool Circle(const std::shared_ptr<data::Geom>& pGeom);
	bool Rectangle(const std::shared_ptr<data::Geom>& pGeom);
	bool Polygon(const std::shared_ptr<data::Geom>& pGeom);
};

class GLDisplay
{
public:
	GLDisplay();
	~GLDisplay();

	void Display(const std::shared_ptr<data::Topo>& pTopo);

private:
	GLdouble m_color[3];
	GLfloat m_lineWidth;
	GLfloat m_pointSize;
	GLint m_polygonMode[2];
};
#endif // GL_OBJECT_H
//------------------------------------------------------------------