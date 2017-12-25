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

// GL Display
GLDisplay::GLDisplay()
{
	// get the previous state
	glGetDoublev(GL_CURRENT_COLOR, m_color);
	glGetIntegerv(GL_POLYGON_MODE, m_polygonMode);
	glGetFloatv(GL_LINE_WIDTH, &m_lineWidth);
	glGetFloatv(GL_POINT_SIZE, &m_pointSize);
}

GLDisplay::~GLDisplay()
{
	// reset to previous state
	glLineWidth(m_lineWidth);
	glPointSize(m_pointSize);
	glColor3d(m_color[0], m_color[1], m_color[2]);
	glPolygonMode(GL_FRONT, m_polygonMode[0]);
}

void GLDisplay::Display(const std::shared_ptr<data::Topo>& pTopo)
{
	glColor3d(pTopo->m_display.m_color[0], pTopo->m_display.m_color[1], pTopo->m_display.m_color[2]);
	glLineWidth(pTopo->m_display.m_lineWidth);
	glPointSize(pTopo->m_display.m_pointSize);

	glPolygonMode(GL_FRONT, GL_FILL);
	if (pTopo->m_display.m_mode == data::DisplayType::DISPLY_LINE)
		glPolygonMode(GL_FRONT, GL_LINE);
	else if (pTopo->m_display.m_mode == data::DisplayType::DISPLY_POINT)
		glPolygonMode(GL_FRONT, GL_POINT);
}