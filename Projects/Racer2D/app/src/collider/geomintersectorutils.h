//------------------------------------------------------------------
//
// Intersector util Declaration for geom
//
//------------------------------------------------------------------
#ifndef GEOM_INTERSECTOR_UTILS_H
#define GEOM_INTERSECTOR_UTILS_H

#include "data\data.h"
#include "data\geom.h"

class GeomIntersectorUtils
{
public:
	// check if the points after projection on the axis(pt2-pt1) lie in between the endpoints
	static bool IsOveralapping(const std::shared_ptr<data::Point>& pt1, const std::shared_ptr<data::Point>& pt2,
					const std::vector<std::shared_ptr<data::Point> >& pPoints);

	// get the min and max len of points after projection on the axis(pt2-pt1)
	static void GetMinMaxLen(const std::shared_ptr<data::Point>& pt1, const std::shared_ptr<data::Point>& pt2,
					const std::vector<std::shared_ptr<data::Point> >& pPoints, double& minLen, double& maxLen);
	
};
#endif // GEOM_INTERSECTOR_UTILS_H
//------------------------------------------------------------------