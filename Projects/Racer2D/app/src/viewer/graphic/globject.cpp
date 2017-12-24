//------------------------------------------------------------------
//
// GL Object to draw
//
//------------------------------------------------------------------
#include "viewer\graphic\globject.h"

GLObject::GLObject(GLenum mode)
{
	glBegin(mode);
}

GLObject::~GLObject()
{
	glEnd();
}

bool GLObject::Point(const std::shared_ptr<data::Geom>& pGeom)
{
	std::shared_ptr<data::Point> pPoint = std::dynamic_pointer_cast<data::Point>(pGeom);
	if (pPoint == nullptr)
		return false;

	glVertex3d(pPoint->m_x, pPoint->m_y, pPoint->m_z);
	return true;
}

bool GLObject::Line(const std::shared_ptr<data::Geom>& pGeom)
{
	std::shared_ptr<data::Line> pLine = std::dynamic_pointer_cast<data::Line>(pGeom);
	if (pLine == nullptr)
		return false;

	glVertex3d(pLine->m_p1.m_x, pLine->m_p1.m_y, pLine->m_p1.m_z);
	glVertex3d(pLine->m_p2.m_x, pLine->m_p2.m_y, pLine->m_p2.m_z);
	return true;
}

bool GLObject::Circle(const std::shared_ptr<data::Geom>& pGeom)
{
	std::shared_ptr<data::Circle> pCircle = std::dynamic_pointer_cast<data::Circle>(pGeom);
	if (pCircle == nullptr)
		return false;

	constexpr double fact = 3.141592653589 / 180;
	for (int i = 0; i < 360; i += 20)
	{
		double theta = i*fact;
		double x = pCircle->m_center.m_x + cos(theta)*pCircle->m_radius;
		double y = pCircle->m_center.m_y + sin(theta)*pCircle->m_radius;
		glVertex3d(x, y, pCircle->m_center.m_z);
	}
	return true;
}

bool GLObject::Rectangle(const std::shared_ptr<data::Geom>& pGeom)
{
	std::shared_ptr<data::Rectangle> pRectangle = std::dynamic_pointer_cast<data::Rectangle>(pGeom);
	if (pRectangle == nullptr)
		return false;

	for (auto pts : pRectangle->m_box)
		glVertex3d(pts->m_x, pts->m_y, pts->m_z);
	return true;
}

bool GLObject::Polygon(const std::shared_ptr<data::Geom>& pGeom)
{
	std::shared_ptr<data::Polygon> pPolygon = std::dynamic_pointer_cast<data::Polygon>(pGeom);
	if (pPolygon == nullptr)
		return false;

	for (auto pts : pPolygon->m_points)
		glVertex3d(pts->m_x, pts->m_y, pts->m_z);
	return true;
}