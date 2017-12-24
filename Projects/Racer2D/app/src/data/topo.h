//------------------------------------------------------------------
//
// Topo class Declaration (Data type for holding Topology)
//
//------------------------------------------------------------------
#ifndef TOPO_H
#define TOPO_H

#include "data\data.h"
#include "data\display.h"
#include "data\geom.h"

namespace data
{
	// Data type for holding data (Topology)
	enum class TopoType
	{
		PART,
		ASSEMBLY,
	};

	class Entity;
	class Display;
	class Geom;

	class Topo : public Entity
	{
	public:
		Topo();
		virtual ~Topo();
		virtual TopoType GetType() const = 0;
		virtual bool ComputeEncloseBox();
		virtual void SetDisplay(const Display& disply);
		EntityType GetEntityType() override;

	public:
		// common attributes
		long m_id;
		std::string m_name;
		Display m_display;
		std::shared_ptr<Geom> m_boxGeom;
	};

	class Part : public Topo
	{
	public:
		Part(std::shared_ptr<Geom>& pGeom);
		virtual ~Part();
		TopoType GetType() const override;
		void GetBoundingBox(double min[], double max[]) const override;
		void Transform(const Matrix& mat) override;

	public:
		std::shared_ptr<Geom> m_geom;
		Matrix m_transform;
	};

	class Assembly : public Topo
	{
	public:
		Assembly();
		virtual ~Assembly();
		TopoType GetType() const override;
		void GetBoundingBox(double min[], double max[]) const override;
		void Transform(const Matrix& mat) override;
		void SetDisplay(const Display& disply) override;

	public:
		std::vector<std::shared_ptr<Part> > m_components;
	};
}
#endif //TOPO_H
//------------------------------------------------------------------