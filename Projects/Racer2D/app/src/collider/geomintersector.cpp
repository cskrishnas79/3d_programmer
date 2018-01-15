//------------------------------------------------------------------
//
// Intersector Implementation for geom
//
//------------------------------------------------------------------
#include "collider\geomintersector.h"
#include "collider\geomintersectorutils.h"
#include "data\utility.h"

// Public methods for Geom
bool GeomIntersector::Intersect(const std::shared_ptr<data::Geom>& pGeom1, const std::shared_ptr<data::Geom>& pGeom2)
{
	bool bRes = false;
	data::GeomType type1 = pGeom1->GetType();
	data::GeomType type2 = pGeom2->GetType();

	if (type1 == data::GeomType::GEOM_LINE)
	{
		std::shared_ptr<data::Line> pLine1 = std::dynamic_pointer_cast<data::Line>(pGeom1);
		if (type2 == data::GeomType::GEOM_LINE)
		{
			std::shared_ptr<data::Line> pLine2 = std::dynamic_pointer_cast<data::Line>(pGeom2);
			bRes = Intersect(pLine1, pLine2);
		}
		else if (type2 == data::GeomType::GEOM_RECTANGLE)
		{
			std::shared_ptr<data::Rectangle> pRec = std::dynamic_pointer_cast<data::Rectangle>(pGeom2);
			bRes = Intersect(pLine1, pRec);
		}
		else if (type2 == data::GeomType::GEOM_CIRCLE)
		{
			std::shared_ptr<data::Circle> pCirc = std::dynamic_pointer_cast<data::Circle>(pGeom2);
			bRes = Intersect(pLine1, pCirc);
		}
		else if (type2 == data::GeomType::GEOM_POLYGON)
		{
			std::shared_ptr<data::Polygon> pPly = std::dynamic_pointer_cast<data::Polygon>(pGeom2);
			bRes = Intersect(pLine1, pPly);
		}
	}
	else if (type1 == data::GeomType::GEOM_RECTANGLE)
	{
		std::shared_ptr<data::Rectangle> pRec1 = std::dynamic_pointer_cast<data::Rectangle>(pGeom1);
		if (type2 == data::GeomType::GEOM_LINE)
		{
			std::shared_ptr<data::Line> pLine = std::dynamic_pointer_cast<data::Line>(pGeom2);
			bRes = Intersect(pLine, pRec1);
		}
		else if (type2 == data::GeomType::GEOM_RECTANGLE)
		{
			std::shared_ptr<data::Rectangle> pRec2 = std::dynamic_pointer_cast<data::Rectangle>(pGeom2);
			bRes = Intersect(pRec1, pRec2);
		}
		else if (type2 == data::GeomType::GEOM_CIRCLE)
		{
			std::shared_ptr<data::Circle> pCirc = std::dynamic_pointer_cast<data::Circle>(pGeom2);
			bRes = Intersect(pRec1, pCirc);
		}
		else if (type2 == data::GeomType::GEOM_POLYGON)
		{
			std::shared_ptr<data::Polygon> pPly = std::dynamic_pointer_cast<data::Polygon>(pGeom2);
			bRes = Intersect(pRec1, pPly);
		}
	}
	else if (type1 == data::GeomType::GEOM_CIRCLE)
	{
		std::shared_ptr<data::Circle> pCirc1 = std::dynamic_pointer_cast<data::Circle>(pGeom1);
		if (type2 == data::GeomType::GEOM_LINE)
		{
			std::shared_ptr<data::Line> pLine = std::dynamic_pointer_cast<data::Line>(pGeom2);
			bRes = Intersect(pLine, pCirc1);
		}
		else if (type2 == data::GeomType::GEOM_RECTANGLE)
		{
			std::shared_ptr<data::Rectangle> pRec = std::dynamic_pointer_cast<data::Rectangle>(pGeom2);
			bRes = Intersect(pRec, pCirc1);
		}
		else if (type2 == data::GeomType::GEOM_CIRCLE)
		{
			std::shared_ptr<data::Circle> pCirc2 = std::dynamic_pointer_cast<data::Circle>(pGeom2);
			bRes = Intersect(pCirc1, pCirc2);
		}
		else if (type2 == data::GeomType::GEOM_POLYGON)
		{
			std::shared_ptr<data::Polygon> pPly = std::dynamic_pointer_cast<data::Polygon>(pGeom2);
			bRes = Intersect(pCirc1, pPly);
		}
	}
	else if (type1 == data::GeomType::GEOM_POLYGON)
	{
		std::shared_ptr<data::Polygon> pPly1 = std::dynamic_pointer_cast<data::Polygon>(pGeom1);
		if (type2 == data::GeomType::GEOM_LINE)
		{
			std::shared_ptr<data::Line> pLine = std::dynamic_pointer_cast<data::Line>(pGeom2);
			bRes = Intersect(pLine, pPly1);
		}
		else if (type2 == data::GeomType::GEOM_RECTANGLE)
		{
			std::shared_ptr<data::Rectangle> pRec = std::dynamic_pointer_cast<data::Rectangle>(pGeom2);
			bRes = Intersect(pRec, pPly1);
		}
		else if (type2 == data::GeomType::GEOM_CIRCLE)
		{
			std::shared_ptr<data::Circle> pCirc = std::dynamic_pointer_cast<data::Circle>(pGeom2);
			bRes = Intersect(pCirc, pPly1);
		}
		else if (type2 == data::GeomType::GEOM_POLYGON)
		{
			std::shared_ptr<data::Polygon> pPly2 = std::dynamic_pointer_cast<data::Polygon>(pGeom2);
			bRes = Intersect(pPly1, pPly2);
		}
	}
	return bRes;
}

bool GeomIntersector::Contain(const std::shared_ptr<data::Point>& ent1, const std::shared_ptr<data::Line>& ent2)
{
	bool bRes = false;
	return bRes;
}

bool GeomIntersector::Contain(const std::shared_ptr<data::Point>& ent1, const std::shared_ptr<data::Rectangle>& ent2)
{
	bool bRes = false;
	return bRes;
}

bool GeomIntersector::Contain(const std::shared_ptr<data::Point>& ent1, const std::shared_ptr<data::Circle>& ent2)
{
	bool bRes = false;
	return bRes;
}

bool GeomIntersector::Contain(const std::shared_ptr<data::Point>& ent1, const std::shared_ptr<data::Polygon>& ent2)
{
	bool bRes = false;
	return bRes;
}

// Line intersection with other entities
bool GeomIntersector::Intersect(const std::shared_ptr<data::Line>& ent1, const std::shared_ptr<data::Line>& ent2)
{
	bool bRes = false;
	return bRes;
}

bool GeomIntersector::Intersect(const std::shared_ptr<data::Line>& ent1, const std::shared_ptr<data::Rectangle>& ent2)
{
	bool bRes = false;
	return bRes;
}

bool GeomIntersector::Intersect(const std::shared_ptr<data::Line>& ent1, const std::shared_ptr<data::Circle>& ent2)
{
	bool bRes = false;
	return bRes;
}

bool GeomIntersector::Intersect(const std::shared_ptr<data::Line>& ent1, const std::shared_ptr<data::Polygon>& ent2)
{
	bool bRes = false;
	return bRes;
}

// Rectangle intersection with other entities
bool GeomIntersector::Intersect(const std::shared_ptr<data::Rectangle>& ent1, const std::shared_ptr<data::Rectangle>& ent2)
{
	// Find intersection along the first rectangle direction
	{	
		const std::shared_ptr<data::Point>& pt1 = ent1->m_box[0];
		const std::shared_ptr<data::Point>& pt2 = ent1->m_box[1];
		const std::shared_ptr<data::Point>& pt3 = ent1->m_box[2];

		// Find along the first direction
		bool bRes = GeomIntersectorUtils::IsOveralapping(pt1, pt2, ent2->m_box);
		if (bRes == false)
			return bRes;

		// Find along the second direction
		bRes = GeomIntersectorUtils::IsOveralapping(pt2, pt3, ent2->m_box);
		if (bRes == false)
			return bRes;
	}

	// now along the second rectangle direction
	{		
		const std::shared_ptr<data::Point>& pt1 = ent2->m_box[0];
		const std::shared_ptr<data::Point>& pt2 = ent2->m_box[1];
		const std::shared_ptr<data::Point>& pt3 = ent2->m_box[2];

		// Find along the first direction
		bool bRes = GeomIntersectorUtils::IsOveralapping(pt1, pt2, ent1->m_box);
		if (bRes == false)
			return bRes;

		// Find along the second direction
		bRes = GeomIntersectorUtils::IsOveralapping(pt2, pt3, ent1->m_box);
		if (bRes == false)
			return bRes;
	}
	return true;
}

bool GeomIntersector::Intersect(const std::shared_ptr<data::Rectangle>& ent1, const std::shared_ptr<data::Circle>& ent2)
{
	double radius = ent2->m_radius;
	const data::Point& pCenter = ent2->m_center;
	// check if the corners of rectangle lies inside circle
	const auto sqr = [](const auto &x) {return x * x; };
	for (const auto &pt : ent1->m_box)
	{
		double dist = sqr(pt->m_x - pCenter.m_x) + sqr(pt->m_y - pCenter.m_y) + sqr(pt->m_z - pCenter.m_z);
		if (dist <= sqr(radius))
			return true;
	}

	// also check with the center of the rectangle
	double dist = sqr(ent1->m_center.m_x - pCenter.m_x) + sqr(ent1->m_center.m_y - pCenter.m_y) + sqr(ent1->m_center.m_z - pCenter.m_z);
	if (dist <= sqr(radius))
		return true;

	// find the extreme points of the circle along the rectangle direction. Get the box 
	// of the rectangle since it may have got transformed
	const std::shared_ptr<data::Point>& pt1 = ent1->m_box[0];
	const std::shared_ptr<data::Point>& pt2 = ent1->m_box[1];
	const std::shared_ptr<data::Point>& pt3 = ent1->m_box[2];

	std::vector<std::shared_ptr<data::Point> > extremes;

	Vector center(pCenter.m_x, pCenter.m_y, pCenter.m_z);
	double cen[3] = { center.get()[0], center.get()[1], center.get()[2] };
	extremes.push_back(std::make_shared<data::Point>(cen));

	Vector c1(pt1->m_x, pt1->m_y, pt1->m_z), c2(pt2->m_x, pt2->m_y, pt2->m_z), c3(pt3->m_x, pt3->m_y, pt3->m_z);
	Vector v21 = c2 - c1;
	Vector u21 = v21.normalize();

	// find extreme points in first direction
	Vector p1 = center + u21*radius; //+ve
	double cen1[3] = { p1.get()[0], p1.get()[1], p1.get()[2] };
	extremes.push_back(std::make_shared<data::Point>(cen1));

	Vector p2 = center + u21*-radius; //-ve
	double cen2[3] = { p2.get()[0], p2.get()[1], p2.get()[2] };
	extremes.push_back(std::make_shared<data::Point>(cen2));

	Vector v32 = c3 - c2;
	Vector u32 = v32.normalize();
	// find extreme points in second direction
	Vector p3 = center + u32*radius; //+ve
	double cen3[3] = { p3.get()[0], p3.get()[1], p3.get()[2] };
	extremes.push_back(std::make_shared<data::Point>(cen3));

	Vector p4 = center + u32*-radius; //-ve
	double cen4[3] = { p4.get()[0], p4.get()[1], p4.get()[2] };
	extremes.push_back(std::make_shared<data::Point>(cen4));

	// Project the extreme points and see if it lies in between the extremes of rectangle
	double minDir1 = 0.0, maxDir1 = Utility::GetProjectedLen(pt1, pt2, pt2);
	double minDir2 = 0.0, maxDir2 = Utility::GetProjectedLen(pt2, pt3, pt3);
	for (const auto& pPoint : extremes)
	{
		double len1 = Utility::GetProjectedLen(pt1, pt2, pPoint);
		double len2 = Utility::GetProjectedLen(pt2, pt3, pPoint);

		if (minDir1 <= len1 && len1 <= maxDir1 && minDir2 <= len2 && len2 <= maxDir2)
			return true;
	}

	/* 
	Case thin and long rectangle intersecting circle in between center and one extreme point,
	and center of rectangle lie outside circle

						Rec _
						   | |
				+ve	cir	3  | |
						|  | |
						|  | |
					cen |  | |
		-ve	cir	2-------|------- cir 1 +ve
						|  | |
						|  | |
						|  | |
				-ve	cir 4  | |
					       | |
						    -
	Take the projection of rectangle center on axis (cir 2 - cir 1) and check if the projected distance
	lies within cir 1 and cir 2. Similarly check on axis (cir 4 - cir 3) in case the rectangle
	is perpendicular. Also check if the extents of the rectangle at that point lie on one side or on either side.
	*/

	// Get extreme point of the circle. First point in the extreme is center so ignore it
	const std::shared_ptr<data::Point>& circ1 = extremes[1];
	const std::shared_ptr<data::Point>& circ2 = extremes[2];
	const std::shared_ptr<data::Point>& circ3 = extremes[3];
	const std::shared_ptr<data::Point>& circ4 = extremes[4];

	std::shared_ptr<data::Point> pRecCenter = std::make_shared<data::Point>(ent1->m_center);
	// Find along first direction
	double dia = 2 * radius;
	double len1 = Utility::GetProjectedLen(circ1, circ2, pRecCenter);
	if (0.0 <= len1 && len1 <= dia)
	{
		// find the min and max distance of the chord at len1. Find the extremes of the rectangle
		// along the chord perpendicular to axis
		double distance = 0.0;
		if (len1 > radius)
			distance = len1 - radius;
		else
			distance = radius - len1;

		double theta = acos(distance / radius);
		double heightFromAxis = radius*sin(theta);
		double minEnt2 = radius - heightFromAxis;
		double maxEnt2 = radius + heightFromAxis;

		double minEnt1 = 0.0, maxEnt1 = 0.0;
		GeomIntersectorUtils::GetMinMaxLen(circ3, circ4, ent1->m_box, minEnt1, maxEnt1);
		if (minEnt1 > maxEnt2)
			return false;
		else if (maxEnt1 < minEnt2)
			return false;
		return true;
	}

	// Find along second direction
	double len2 = Utility::GetProjectedLen(circ3, circ4, pRecCenter);
	if (0.0 <= len2 && len2 <= dia)
	{
		// find the min and max distance of the chord at len2. Find the extremes of the rectangle
		// along the chord perpendicular to axis
		double distance = 0.0;
		if (len2 > radius)
			distance = len2 - radius;
		else
			distance = radius - len2;

		double theta = acos(distance / radius);
		double heightFromAxis = radius*sin(theta);
		double minEnt2 = radius - heightFromAxis;
		double maxEnt2 = radius + heightFromAxis;

		double minEnt1 = 0.0, maxEnt1 = 0.0;
		GeomIntersectorUtils::GetMinMaxLen(circ1, circ2, ent1->m_box, minEnt1, maxEnt1);
		if (minEnt1 > maxEnt2)
			return false;
		else if (maxEnt1 < minEnt2)
			return false;
		return true;
	}
	return false;
}

bool GeomIntersector::Intersect(const std::shared_ptr<data::Rectangle>& ent1, const std::shared_ptr<data::Polygon>& ent2)
{
	bool bRes = false;
	return bRes;
}

// Circle intersection with other entities
bool GeomIntersector::Intersect(const std::shared_ptr<data::Circle>& ent1, const std::shared_ptr<data::Circle>& ent2)
{
	const auto sqr = [](const auto &x) { return x * x; };
	double x = sqr(ent1->m_center.m_x - ent2->m_center.m_x);
	double y = sqr(ent1->m_center.m_y - ent2->m_center.m_y);
	double z = sqr(ent1->m_center.m_z - ent2->m_center.m_z);
	double sqrSum = x + y + z;
	double radSum = sqr(ent1->m_radius + ent2->m_radius);
	if (sqrSum <= radSum)
		return true;
	return false;
}

bool GeomIntersector::Intersect(const std::shared_ptr<data::Circle>& ent1, const std::shared_ptr<data::Polygon>& ent2)
{
	bool bRes = false;
	return bRes;
}

// Polygon intersection with other entities
bool GeomIntersector::Intersect(const std::shared_ptr<data::Polygon>& ent1, const std::shared_ptr<data::Polygon>& ent2)
{
	bool bRes = false;
	return bRes;
}