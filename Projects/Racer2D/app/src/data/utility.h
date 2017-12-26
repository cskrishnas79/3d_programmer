//------------------------------------------------------------------
//
// Utility class Declaration
//
//------------------------------------------------------------------
#ifndef UTILITY_H
#define UTILITY_H

#include "data\data.h"
#include "data\geom.h"
#include "data\topo.h"

class Utility
{
public:

	static std::shared_ptr<data::Geom> CopyGeom(const std::shared_ptr<data::Geom>& pGeom);

	static double GetProjectedLen(const data::Point& pPoint1, const data::Point& pPoint2, 
								const data::Point& pPoint);
};
#endif // UTILITY_H
//------------------------------------------------------------------
