//------------------------------------------------------------------
//
// Intersector Declaration for geom
//
//------------------------------------------------------------------
#ifndef GEOM_INTERSECTOR_H
#define GEOM_INTERSECTOR_H

#include "data\data.h"
#include "data\geom.h"

class GeomIntersector
{
public:

	static bool Intersect(const std::shared_ptr<data::Geom>& pGeom1, const std::shared_ptr<data::Geom>& pGeom2);

	// Check if point is inside/on 
	static bool Contain(const std::shared_ptr<data::Point>& ent1, const std::shared_ptr<data::Line>& ent2);
	static bool Contain(const std::shared_ptr<data::Point>& ent1, const std::shared_ptr<data::Rectangle>& ent2);
	static bool Contain(const std::shared_ptr<data::Point>& ent1, const std::shared_ptr<data::Circle>& ent2);
	static bool Contain(const std::shared_ptr<data::Point>& ent1, const std::shared_ptr<data::Polygon>& ent2);

	// Check if line intersect
	static bool Intersect(const std::shared_ptr<data::Line>& ent1, const std::shared_ptr<data::Line>& ent2);
	static bool Intersect(const std::shared_ptr<data::Line>& ent1, const std::shared_ptr<data::Rectangle>& ent2);
	static bool Intersect(const std::shared_ptr<data::Line>& ent1, const std::shared_ptr<data::Circle>& ent2);
	static bool Intersect(const std::shared_ptr<data::Line>& ent1, const std::shared_ptr<data::Polygon>& ent2);

	// Check if rectangle intersect
	static bool Intersect(const std::shared_ptr<data::Rectangle>& ent1, const std::shared_ptr<data::Rectangle>& ent2);
	static bool Intersect(const std::shared_ptr<data::Rectangle>& ent1, const std::shared_ptr<data::Circle>& ent2);
	static bool Intersect(const std::shared_ptr<data::Rectangle>& ent1, const std::shared_ptr<data::Polygon>& ent2);

	// Check if circle intersect
	static bool Intersect(const std::shared_ptr<data::Circle>& ent1, const std::shared_ptr<data::Circle>& ent2);
	static bool Intersect(const std::shared_ptr<data::Circle>& ent1, const std::shared_ptr<data::Polygon>& ent2);

	// Check if polygon intersect
	static bool Intersect(const std::shared_ptr<data::Polygon>& ent1, const std::shared_ptr<data::Polygon>& ent2);
};
#endif // GEOM_INTERSECTOR_H
//------------------------------------------------------------------