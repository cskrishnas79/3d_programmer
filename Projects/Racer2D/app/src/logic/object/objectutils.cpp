// ------------------------------------------------------------------
//
// Object Utility Implementation
//
//------------------------------------------------------------------

#include "logic\object\objectutils.h"
#include "data\utility.h"

bool ObjectUtils::GetPosAndDirection(const std::shared_ptr<data::Entity>& pPath, const float& interval,
								const float& speed, double prevPos[3], double nextPos[3], double dir[3])
{
	bool bRes = false;
	if (pPath->GetEntityType() == data::EntityType::ENT_TOPO)
	{
		std::shared_ptr<data::Topo> pTopo = std::dynamic_pointer_cast<data::Topo>(pPath);
		if (pTopo->GetType() == data::TopoType::TOPO_PART)
		{
			std::shared_ptr<data::Part> pPart = std::dynamic_pointer_cast<data::Part>(pTopo);
			std::shared_ptr<data::Geom>& pGeom = pPart->m_geom;

			std::shared_ptr<data::Geom> pCloneGeom = pGeom->Clone();
			pCloneGeom->Transform(pPart->m_transform);
			bRes = GetPosAndDirection(pCloneGeom, interval, speed, prevPos, nextPos, dir);
		}
	}
	else if (pPath->GetEntityType() == data::EntityType::ENT_GEOM)
	{

	}
	return bRes;
}

bool ObjectUtils::GetPosAndDirection(const std::shared_ptr<data::Geom>& pGeom, const float& interval,
							const float& speed, double prevPos[3], double nextPos[3], double dir[3])
{
	bool bRes = false;
	if (pGeom->GetType() == data::GeomType::GEOM_LINE)
	{
		std::shared_ptr<data::Line> pLine = std::dynamic_pointer_cast<data::Line>(pGeom);
		double start[3] = { pLine->m_p1.m_x, pLine->m_p1.m_y, pLine->m_p1.m_z };
		double end[3] = { pLine->m_p2.m_x, pLine->m_p2.m_y, pLine->m_p2.m_z };

		Vector vStart(start); Vector vEnd(end);
		Vector vDir = vEnd - vStart;
		Vector uDir = vDir.normalize();

		float mag = speed*interval;
		Vector vNext = vStart + uDir*mag;

		Vector vNextDir = vEnd - vNext;
		double distance = vNextDir.length();
		double dot = vDir.dot(vNextDir);
		if (dot >= 0.0)
		{
			const double* val = vNext.get();
			if (dot == 0.0)
				val = vEnd.get();

			nextPos[0] = val[0]; nextPos[1] = val[1]; nextPos[2] = val[2];
			val = uDir.get();
			dir[0] = val[0]; dir[1] = val[1]; dir[2] = val[2];
			bRes = true;
		}
	}
	return bRes;
}