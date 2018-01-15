//------------------------------------------------------------------
//
// Intersector Implementation for Topology
//
//------------------------------------------------------------------
#include "collider\topointersector.h"
#include "collider\geomintersector.h"
#include "data\utility.h"

TopoIntersector::TopoIntersector()
{
}

TopoIntersector::~TopoIntersector()
{
	m_intersectingTopos.clear();
}

// Public Methods
bool TopoIntersector::Intersect(const std::shared_ptr<data::Topo>& pTopo1, const std::shared_ptr<data::Topo>& pTopo2)
{
	bool bRes = false;
	data::TopoType type1 = pTopo1->GetType();
	data::TopoType type2 = pTopo2->GetType();

	if (type1 == data::TopoType::TOPO_ASSEMBLY)
	{
		std::shared_ptr<data::Assembly> pAssem1 = std::dynamic_pointer_cast<data::Assembly>(pTopo1);
		if (type2 == data::TopoType::TOPO_ASSEMBLY)
		{
			std::shared_ptr<data::Assembly> pAssem2 = std::dynamic_pointer_cast<data::Assembly>(pTopo2);
			bRes = Intersect(pAssem1, pAssem2);
		}
		else if (type2 == data::TopoType::TOPO_PART)
		{
			std::shared_ptr<data::Part> pPart = std::dynamic_pointer_cast<data::Part>(pTopo2);
			bRes = Intersect(pPart, pAssem1, true);
		}
	}
	else if (type1 == data::TopoType::TOPO_PART)
	{
		std::shared_ptr<data::Part> pPart1 = std::dynamic_pointer_cast<data::Part>(pTopo1);
		if (type2 == data::TopoType::TOPO_ASSEMBLY)
		{
			std::shared_ptr<data::Assembly> pAssem = std::dynamic_pointer_cast<data::Assembly>(pTopo2);
			bRes = Intersect(pPart1, pAssem, true);
		}
		else if (type2 == data::TopoType::TOPO_PART)
		{
			std::shared_ptr<data::Part> pPart2 = std::dynamic_pointer_cast<data::Part>(pTopo2);
			bRes = Intersect(pPart1, pPart2);
		}
	}
	return bRes;
}

// Private methods for Topo
bool TopoIntersector::Intersect(const std::shared_ptr<data::Assembly>& pEnt1, const std::shared_ptr<data::Assembly>& pEnt2)
{
	bool bRes = false;
	// Keep the first assembly and get all the parts from the second assembly and try to see 
	// which parts are intersecting
	std::vector<std::shared_ptr<data::Part> > components2;
	int len2 = (int)pEnt2->m_components.size();
	for (const auto& part : pEnt2->m_components)
	{
		bool bIntersect = Intersect(part, pEnt1);
		if (bIntersect == false)
			continue;

		components2.push_back(part);
	}

	len2 = (int)components2.size();
	if (len2 == 0)
		return bRes;

	// Keep the second assembly and get all the parts from the first assembly and try to see 
	// which parts are intersecting
	std::vector<std::shared_ptr<data::Part> > components1;
	int len1 = (int)pEnt1->m_components.size();
	for (const auto& part : pEnt1->m_components)
	{
		bool bIntersect = Intersect(part, pEnt2);
		if (bIntersect == false)
			continue;

		components1.push_back(part);
	}
	
	len1 = (int)components1.size();
	if (len1 == 0)
		return bRes;

	// check parts in the first assembly intersecting with parts of second assembly
	for (const auto& part2 : components2)
	{
		for (const auto& part1 : components1)
		{
			bool bIntersect = Intersect(part1, part2);
			if (bIntersect == false)
				continue;

			bRes = bIntersect;
		}
	}
	return bRes;
}

bool TopoIntersector::Intersect(const std::shared_ptr<data::Part>& pEnt1, const std::shared_ptr<data::Assembly>& pEnt2,
								bool bDetailCheck)
{
	std::shared_ptr<data::Geom>& pGeom1 = pEnt1->m_geom;
	std::shared_ptr<data::Geom> pCloneGeom1 = pGeom1->Clone(); // Utility::CopyGeom(pGeom1);
	pCloneGeom1->Transform(pEnt1->m_transform);

	std::shared_ptr<data::Geom>& pBox2 = pEnt2->m_boxGeom;
	bool bRes = GeomIntersector::Intersect(pCloneGeom1, pBox2);
	if (bRes == false)
		return bRes;

	if (bDetailCheck == false)
		return bRes;

	int len = (int)pEnt2->m_components.size();
	for (const auto& part : pEnt2->m_components)
	{
		bool bIntersect = Intersect(pEnt1, part);
		if (bIntersect == false)
			continue;

		bRes = bIntersect;
	}
	return bRes;
}

bool TopoIntersector::Intersect(const std::shared_ptr<data::Part>& pEnt1, const std::shared_ptr<data::Part>& pEnt2)
{
	std::shared_ptr<data::Geom>& pGeom1 = pEnt1->m_geom;
	std::shared_ptr<data::Geom>& pGeom2 = pEnt2->m_geom;

	// create copy, transform and then find intersection
	std::shared_ptr<data::Geom> pCloneGeom1 = pGeom1->Clone(); // Utility::CopyGeom(pGeom1);
	std::shared_ptr<data::Geom> pCloneGeom2 = pGeom2->Clone(); // Utility::CopyGeom(pGeom2);

	pCloneGeom1->Transform(pEnt1->m_transform);
	pCloneGeom2->Transform(pEnt2->m_transform);

	bool bRes = GeomIntersector::Intersect(pCloneGeom1, pCloneGeom2);
	if (bRes == true)
	{
		std::shared_ptr<data::Topo> pTopo1 = std::dynamic_pointer_cast<data::Topo>(pEnt1);
		m_intersectingTopos.push_back(pTopo1);

		std::shared_ptr<data::Topo> pTopo2 = std::dynamic_pointer_cast<data::Topo>(pEnt2);
		m_intersectingTopos.push_back(pTopo2);
	}
	return bRes;
}