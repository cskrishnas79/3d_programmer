//------------------------------------------------------------------
//
// Intersector util Declaration for geom
//
//------------------------------------------------------------------
#include "collider\geomintersectorutils.h"
#include "data\utility.h"

bool GeomIntersectorUtils::IsOveralapping(const std::shared_ptr<data::Point>& pt1, const std::shared_ptr<data::Point>& pt2,
	const std::vector<std::shared_ptr<data::Point> >& pPoints)
{
	double minEnt1 = 0.0, maxEnt1 = Utility::GetProjectedLen(pt1, pt2, pt2);
	double minEnt2 = 0.0, maxEnt2 = 0.0;
	GeomIntersectorUtils::GetMinMaxLen(pt1, pt2, pPoints, minEnt2, maxEnt2);

	if (minEnt2 > maxEnt1)
		return false;
	else if (maxEnt2 < minEnt1)
		return false;
	return true;
}

void GeomIntersectorUtils::GetMinMaxLen(const std::shared_ptr<data::Point>& pt1, const std::shared_ptr<data::Point>& pt2,
			const std::vector<std::shared_ptr<data::Point> >& pPoints, double& minLen, double& maxLen)
{
	int i = 0;
	for (const auto& pPoint : pPoints)
	{
		double len = Utility::GetProjectedLen(pt1, pt2, pPoint);
		if (i == 0)
		{
			minLen = maxLen = len; i++;
			continue;
		}
		minLen = MIN(minLen, len);
		maxLen = MAX(maxLen, len);
	}
}