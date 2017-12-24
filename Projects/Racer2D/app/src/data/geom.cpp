//------------------------------------------------------------------
//
// Geom class Implementation (Geom class for basic primitive shapes)
//
//------------------------------------------------------------------
#include "data\geom.h"


namespace data
{
	Geom::Geom()
	{
	}

	Geom::~Geom()
	{
	}

	EntityType Geom::GetEntityType()
	{
		return EntityType::ENT_GEOM;
	}
	//------------------------------------------------------------------

	Point::Point() : m_x(0.0), m_y(0.0), m_z(0.0)
	{
	}

	Point::Point(double point[]) : m_x(point[0]), m_y(point[1]), m_z(point[2])
	{
	}

	Point::~Point()
	{
	}

	Point::Point(const Point& point)
	{
		m_x = point.m_x; m_y = point.m_y; m_z = point.m_z;
	}

	Point& Point::operator=(const Point& point)
	{
		m_x = point.m_x; m_y = point.m_y; m_z = point.m_z;
		return (*this);
	}

	GeomType Point::GetType() const
	{
		return GeomType::GEOM_POINT;
	}

	void Point::GetBoundingBox(double min[], double max[]) const
	{
		min[0] = m_x; min[1] = m_y; min[2] = m_z;
		max[0] = m_x; max[1] = m_y; max[2] = m_z;
	}

	void Point::Transform(const Matrix& mat)
	{
		double point[3] = { m_x, m_y, m_z };
		mat*point;
		m_x = point[0]; m_y = point[1]; m_z = point[2];
	}

	Geom* Point::Clone()
	{
		Geom* pPoint = new Point(*this);
		return pPoint;
	}
	//------------------------------------------------------------------

	Line::Line(double start[], double end[]) : m_p1(start), m_p2(end)
	{
	}

	Line::~Line()
	{
	}

	Line::Line(const Line& line)
	{
		m_p1.m_x = line.m_p1.m_x; m_p1.m_y = line.m_p1.m_y; m_p1.m_z = line.m_p1.m_z;
		m_p2.m_x = line.m_p2.m_x; m_p2.m_y = line.m_p2.m_y; m_p2.m_z = line.m_p2.m_z;
	}

	Line& Line::operator=(const Line& line)
	{
		m_p1.m_x = line.m_p1.m_x; m_p1.m_y = line.m_p1.m_y; m_p1.m_z = line.m_p1.m_z;
		m_p2.m_x = line.m_p2.m_x; m_p2.m_y = line.m_p2.m_y; m_p2.m_z = line.m_p2.m_z;
		return (*this);
	}

	GeomType Line::GetType() const
	{
		return GeomType::GEOM_LINE;
	}

	void Line::GetBoundingBox(double min[], double max[]) const
	{
		min[0] = max[0] = m_p1.m_x;
		min[1] = max[1] = m_p1.m_y;
		min[2] = max[2] = m_p1.m_z;

		// now check with next point
		min[0] = MIN(m_p2.m_x, min[0]);
		min[1] = MIN(m_p2.m_y, min[1]);
		min[2] = MIN(m_p2.m_z, min[2]);

		max[0] = MAX(m_p2.m_x, max[0]);
		max[1] = MAX(m_p2.m_y, max[1]);
		max[2] = MAX(m_p2.m_z, max[2]);
	}

	void Line::Transform(const Matrix& mat)
	{
		m_p1.Transform(mat);
		m_p2.Transform(mat);
	}

	Geom* Line::Clone()
	{
		Geom* pLine = new Line(*this);
		return pLine;
	}
	//------------------------------------------------------------------

	Rectangle::Rectangle(double center[], double width, double height)
		: m_width(width), m_height(height), m_center(center)
	{
		double halfWidth = m_width / 2;
		double halfHeight = m_height / 2;
		double xmin = m_center.m_x - halfWidth;
		double xmax = m_center.m_x + halfWidth;
		double ymin = m_center.m_y - halfHeight;
		double ymax = m_center.m_y + halfHeight;

		double pt1[3] = { xmin, ymin, 0.0 }, pt2[3] = { xmax, ymin, 0.0 };
		double pt3[3] = { xmax, ymax, 0.0 }, pt4[3] = { xmin, ymax, 0.0 };
		m_box.push_back(std::make_shared<Point>(pt1));
		m_box.push_back(std::make_shared<Point>(pt2));
		m_box.push_back(std::make_shared<Point>(pt3));
		m_box.push_back(std::make_shared<Point>(pt4));
	}

	Rectangle::Rectangle(double pt1[], double pt2[], double pt3[], double pt4[])
	{
		// create vec1 and vec2 to get the direction of the box
		Vector v1(pt1), v2(pt2), v3(pt3);
		Vector wDir(v1 - v2);
		Vector hDir(v3 - v2);
		m_width = wDir.length();
		m_height = hDir.length();

		m_center.m_x = pt2[0]; m_center.m_y = pt2[1]; m_center.m_z = pt2[2];

		double halfWidth = m_width / 2;
		double halfHeight = m_height / 2;
		// first translate in width direction by half and then in height direction by half
		Vector w = wDir.normalize()*halfWidth;
		const double* wVal = w.get();
		Matrix transW;
		transW.translate(wVal[0], wVal[1], wVal[2]);
		m_center.Transform(transW);

		Vector h = hDir.normalize()*halfHeight;
		const double* hVal = h.get();
		Matrix transH;
		transH.translate(hVal[0], hVal[1], hVal[2]);
		m_center.Transform(transH);
	}

	Rectangle::~Rectangle()
	{
	}

	Rectangle::Rectangle(const Rectangle& rec)
	{
		m_center.m_x = rec.m_center.m_x;
		m_center.m_y = rec.m_center.m_y;
		m_center.m_z = rec.m_center.m_z;
		m_width = rec.m_width;
		m_height = rec.m_height;
		for (auto pts : rec.m_box)
		{
			double val[3] = { pts->m_x, pts->m_y, pts->m_z };
			m_box.push_back(std::make_shared<Point>(val));
		}
	}

	Rectangle& Rectangle::operator=(const Rectangle& rec)
	{
		m_center.m_x = rec.m_center.m_x;
		m_center.m_y = rec.m_center.m_y;
		m_center.m_z = rec.m_center.m_z;
		m_width = rec.m_width;
		m_height = rec.m_height;
		for (auto pts : rec.m_box)
		{
			double val[3] = { pts->m_x, pts->m_y, pts->m_z };
			m_box.push_back(std::make_shared<Point>(val));
		}
		return (*this);
	}

	GeomType Rectangle::GetType() const
	{
		return GeomType::GEOM_RECTANGLE;
	}

	void Rectangle::GetBoundingBox(double min[], double max[]) const
	{
		double xmin = 0, ymin = 0, zmin = 0;
		double xmax = 0, ymax = 0, zmax = 0;
		for (int i = 0; i<(int)m_box.size(); ++i)
		{
			const std::shared_ptr<data::Point>& pPoint = m_box[i];
			if (i == 0)
			{
				xmin = xmax = pPoint->m_x;
				ymin = ymax = pPoint->m_y;
				zmin = zmax = pPoint->m_z;
				continue;
			}

			xmin = MIN(pPoint->m_x, xmin);
			ymin = MIN(pPoint->m_y, ymin);
			zmin = MIN(pPoint->m_z, zmin);

			xmax = MAX(pPoint->m_x, xmax);
			ymax = MAX(pPoint->m_y, ymax);
			zmax = MAX(pPoint->m_z, zmax);
		}

		min[0] = xmin; min[1] = ymin; min[2] = zmin;
		max[0] = xmax; max[1] = ymax; max[2] = zmax;
	}

	void Rectangle::Transform(const Matrix& mat)
	{
		m_center.Transform(mat);
		for (auto pts : m_box)
			pts->Transform(mat);
	}

	Geom* Rectangle::Clone()
	{
		Geom* pRectangle = new Rectangle(*this);
		return pRectangle;
	}
	//------------------------------------------------------------------

	Circle::Circle(double center[], double radius) : m_radius(radius), m_center(center)
	{
	}

	Circle::~Circle()
	{
	}

	Circle::Circle(const Circle& circ)
	{
		m_center.m_x = circ.m_center.m_x;
		m_center.m_y = circ.m_center.m_y;
		m_center.m_z = circ.m_center.m_z;
		m_radius = circ.m_radius;
	}

	Circle& Circle::operator=(const Circle& circ)
	{
		m_center.m_x = circ.m_center.m_x;
		m_center.m_y = circ.m_center.m_y;
		m_center.m_z = circ.m_center.m_z;
		m_radius = circ.m_radius;
		return (*this);
	}

	GeomType Circle::GetType() const
	{
		return GeomType::GEOM_CIRCLE;
	}

	void Circle::GetBoundingBox(double min[], double max[]) const
	{
		double xmin = m_center.m_x - m_radius;
		double xmax = m_center.m_x + m_radius;
		double ymin = m_center.m_y - m_radius;
		double ymax = m_center.m_y + m_radius;

		min[0] = xmin; min[1] = ymin; min[2] = m_center.m_z;
		max[0] = xmax; max[1] = ymax; max[2] = m_center.m_z;
	}

	void Circle::Transform(const Matrix& mat)
	{
		m_center.Transform(mat);
	}

	Geom* Circle::Clone()
	{
		Geom* pCircle = new Circle(*this);
		return pCircle;
	}
	//------------------------------------------------------------------

	Polygon::Polygon()
	{
	}

	Polygon::~Polygon()
	{
	}

	Polygon::Polygon(const Polygon& poly)
	{
		for (auto pts : poly.m_points)
		{
			double val[3] = { pts->m_x, pts->m_y, pts->m_z };
			m_points.push_back(std::make_shared<Point>(val));
		}
	}

	Polygon& Polygon::operator=(const Polygon& poly)
	{
		for (auto pts : poly.m_points)
		{
			double val[3] = { pts->m_x, pts->m_y, pts->m_z };
			m_points.push_back(std::make_shared<Point>(val));
		}
		return (*this);
	}

	GeomType Polygon::GetType() const
	{
		return GeomType::GEOM_POLYGON;
	}

	void Polygon::GetBoundingBox(double min[], double max[]) const
	{
		double xmin = 0, ymin = 0, zmin = 0;
		double xmax = 0, ymax = 0, zmax = 0;
		for (int i = 0; i<(int)m_points.size(); ++i)
		{
			const std::shared_ptr<data::Point>& pPoint = m_points[i];
			if (i == 0)
			{
				xmin = xmax = pPoint->m_x;
				ymin = ymax = pPoint->m_y;
				zmin = zmax = pPoint->m_z;
				continue;
			}

			xmin = MIN(pPoint->m_x, xmin);
			ymin = MIN(pPoint->m_y, ymin);
			zmin = MIN(pPoint->m_z, zmin);

			xmax = MAX(pPoint->m_x, xmax);
			ymax = MAX(pPoint->m_y, ymax);
			zmax = MAX(pPoint->m_z, zmax);
		}

		min[0] = xmin; min[1] = ymin; min[2] = zmin;
		max[0] = xmax; max[1] = ymax; max[2] = zmax;
	}

	void Polygon::Transform(const Matrix& mat)
	{
		for (auto pts : m_points)
			pts->Transform(mat);
	}

	Geom* Polygon::Clone()
	{
		Geom* pPolygon = new Polygon(*this);
		return pPolygon;
	}
}