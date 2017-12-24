//------------------------------------------------------------------
//
// Geom class Declaration (basic primitive shapes)
//
//------------------------------------------------------------------
#ifndef GEOM_H
#define GEOM_H

#include "data\data.h"

namespace data
{
	enum class GeomType
	{
		GEOM_POINT,
		GEOM_LINE,
		GEOM_RECTANGLE,
		GEOM_CIRCLE,
		GEOM_POLYGON
	};

	class Entity;
	class Geom : public Entity
	{
	public:
		Geom();
		virtual ~Geom();
		virtual GeomType GetType() const = 0;
		virtual Geom* Clone() = 0;
		EntityType GetEntityType() override;
	};

	class Point : public Geom
	{
	public:

		Point();
		Point(double point[]);
		virtual ~Point();
		Point(const Point& point);
		Point& operator=(const Point& point);

		GeomType GetType() const override;
		void GetBoundingBox(double min[], double max[]) const override;
		void Transform(const Matrix& mat) override;
		Geom* Clone() override;

	public:
		double m_x;
		double m_y;
		double m_z;
	};

	class Line : public Geom
	{
	public:
		Line(double start[], double end[]);
		virtual ~Line();
		Line(const Line& line);
		Line& operator=(const Line& line);

		GeomType GetType() const override;
		void GetBoundingBox(double min[], double max[]) const override;
		void Transform(const Matrix& mat) override;
		Geom* Clone() override;

	public:
		Point m_p1;
		Point m_p2;
	};

	class Rectangle : public Geom
	{
	public:
		Rectangle(double center[], double width, double height);
		Rectangle(double pt1[], double pt2[], double pt3[], double pt4[]);
		virtual ~Rectangle();
		Rectangle(const Rectangle& rec);
		Rectangle& operator=(const Rectangle& rec);

		GeomType GetType() const override;
		void GetBoundingBox(double min[], double max[]) const override;
		void Transform(const Matrix& mat) override;
		Geom* Clone() override;

	public:
		Point m_center;
		double m_width;
		double m_height;
		std::vector<std::shared_ptr<Point> > m_box; // box 
	};

	class Circle : public Geom
	{
	public:
		Circle(double center[], double radius);
		virtual ~Circle();
		Circle(const Circle& circ);
		Circle& operator=(const Circle& circ);

		GeomType GetType() const override;
		void GetBoundingBox(double min[], double max[]) const override;
		void Transform(const Matrix& mat) override;
		Geom* Clone() override;

	public:
		Point m_center;
		double m_radius;
	};

	class Polygon : public Geom
	{
	public:
		Polygon();
		virtual ~Polygon();
		Polygon(const Polygon& poly);
		Polygon& operator=(const Polygon& poly);

		GeomType GetType() const override;
		void GetBoundingBox(double min[], double max[]) const override;
		void Transform(const Matrix& mat) override;
		Geom* Clone() override;

	public:
		std::vector<std::shared_ptr<Point> > m_points;
	};
}
#endif //GEOM_H
//------------------------------------------------------------------