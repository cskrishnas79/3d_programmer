//------------------------------------------------------------------
//
// Intersector Declaration for Topology
//
//------------------------------------------------------------------
#ifndef TOPO_INTERSECTOR_H
#define TOPO_INTERSECTOR_H

#include "data\data.h"
#include "data\geom.h"
#include "data\topo.h"

class TopoIntersector
{
public:
	TopoIntersector();
	~TopoIntersector();

	bool Intersect(const std::shared_ptr<data::Topo>& pTopo1, const std::shared_ptr<data::Topo>& pTopo2);
	bool Intersect(const std::shared_ptr<data::Assembly>& pEnt1, const std::shared_ptr<data::Assembly>& pEnt2);

	bool Intersect(const std::shared_ptr<data::Part>& pEnt1, const std::shared_ptr<data::Assembly>& pEnt2);
	bool Intersect(const std::shared_ptr<data::Part>& pEnt1, const std::shared_ptr<data::Part>& pEnt2);

public:
	std::vector<std::shared_ptr<data::Topo> > m_intersectingTopos;
};
#endif // TOPO_INTERSECTOR_H
//------------------------------------------------------------------