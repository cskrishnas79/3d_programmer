//------------------------------------------------------------------
//
// Data class Declaration
//
//------------------------------------------------------------------
#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "math\vector.h"
#include "math\matrix.h"

namespace data
{
	enum class EntityType
	{
		GEOM,
		TOPO,
	};

	// Base class for all types of data
	class Entity
	{
	public:
		Entity() {};
		virtual ~Entity() {};
		virtual EntityType GetEntityType() = 0;
		virtual void GetBoundingBox(double min[], double max[]) = 0;
		virtual void Transform(const Matrix& mat) = 0;
	};
}
#endif //DATA_H
//------------------------------------------------------------------