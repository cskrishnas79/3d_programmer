//------------------------------------------------------------------
//
// Topo class Implementation (Data type for holding Topology)
//
//------------------------------------------------------------------
#include "data\topo.h"
#include "data\utility.h"

namespace data
{
	Topo::Topo() : m_id(0), m_name("")
	{
	}

	Topo::~Topo()
	{
	}

	EntityType Topo::GetEntityType()
	{
		return EntityType::TOPO;
	}

	void Topo::SetDisplay(const Display& disply)
	{
		m_display = disply;
	}

	bool Topo::ComputeEncloseBox()
	{
		// Call to this API should be made once the topo is created so that the box
		// is the minimum enclosing box along AABB
		double min[3] = { 0.0,0.0,0.0 }, max[3] = { 0.0,0.0,0.0 };
		GetBoundingBox(min, max);

		double dimHalf[3] = { 0.0,0.0,0.0 }, location[3] = { 0.0,0.0,0.0 };
		dimHalf[0] = (max[0] - min[0]) / 2;
		dimHalf[1] = (max[1] - min[1]) / 2;
		dimHalf[2] = (max[2] - min[2]) / 2;

		// find the cg of the top
		location[0] = min[0] + dimHalf[0];
		location[1] = min[1] + dimHalf[1];
		location[2] = min[2] + dimHalf[2];

		double width = dimHalf[0] * 2;
		double height = dimHalf[1] * 2;

		m_boxGeom = std::make_shared<data::Rectangle>(location, width, height);
		return true;
	}
	//------------------------------------------------------------------

	Part::Part(std::shared_ptr<Geom>& pGeom) : m_geom(pGeom)
	{
	}

	Part::~Part()
	{
	}

	TopoType Part::GetType() const
	{
		return TopoType::PART;
	}

	void Part::GetBoundingBox(double min[], double max[]) const
	{
		std::shared_ptr<data::Geom> pCloneGeom = Utility::CopyGeom(m_geom);
		pCloneGeom->Transform(m_transform);
		pCloneGeom->GetBoundingBox(min, max);
	}

	void Part::Transform(const Matrix& mat)
	{
		m_transform *= mat;

		// also transform bounding box
		if (m_boxGeom)
			m_boxGeom->Transform(mat);
	}
	//------------------------------------------------------------------

	Assembly::Assembly()
	{
	}

	Assembly::~Assembly()
	{
	}

	TopoType Assembly::GetType() const
	{
		return TopoType::ASSEMBLY;
	}

	void Assembly::GetBoundingBox(double min[], double max[]) const
	{
		for (int i = 0; i<(int)m_components.size(); ++i)
		{
			const std::shared_ptr<data::Part>& pPart = m_components[i];
			if (i == 0)
			{
				pPart->GetBoundingBox(min, max);
				continue;
			}

			double minP[3] = { 0.0,0.0,0.0 }, maxP[3] = { 0.0,0.0,0.0 };
			pPart->GetBoundingBox(minP, maxP);
			min[0] = MIN(min[0], minP[0]);
			min[1] = MIN(min[1], minP[1]);
			min[2] = MIN(min[2], minP[2]);

			max[0] = MAX(max[0], maxP[0]);
			max[1] = MAX(max[1], maxP[1]);
			max[2] = MAX(max[2], maxP[2]);
		}
	}

	void Assembly::Transform(const Matrix& mat)
	{
		for (auto part : m_components)
			part->Transform(mat);

		// also transform bounding box
		if (m_boxGeom)
			m_boxGeom->Transform(mat);
	}

	void Assembly::SetDisplay(const Display& disply)
	{
		Topo::SetDisplay(disply);
		// override the display of the topo's contained
		for (auto part : m_components)
			part->SetDisplay(disply);
	}
	//------------------------------------------------------------------
}