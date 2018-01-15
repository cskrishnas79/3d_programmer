//------------------------------------------------------------------
//
// Utility class Implementation
//
//------------------------------------------------------------------
#include "data\utility.h"

double Utility::GetProjectedLen(const std::shared_ptr<data::Point>& pPoint1,
			const std::shared_ptr<data::Point>& pPoint2, const std::shared_ptr<data::Point>& pPoint)
{
	Vector pt1(pPoint1->m_x, pPoint1->m_y, pPoint1->m_z);
	Vector pt2(pPoint2->m_x, pPoint2->m_y, pPoint2->m_z);

	Vector dir(pt2 - pt1);
	Vector uDir = dir.normalize();

	Vector point(pPoint->m_x, pPoint->m_y, pPoint->m_z);
	Vector refToPt(point - pt1);

	double dotLen = uDir.dot(refToPt);
	return dotLen;
}