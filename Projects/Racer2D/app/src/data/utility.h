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

	static double GetProjectedLen(const std::shared_ptr<data::Point>& pPoint1, 
				const std::shared_ptr<data::Point>& pPoint2, const std::shared_ptr<data::Point>& pPoint);
};
#endif // UTILITY_H
//------------------------------------------------------------------
