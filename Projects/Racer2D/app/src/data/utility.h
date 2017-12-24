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

	static std::shared_ptr<data::Geom> CopyGeom(const std::shared_ptr<data::Geom>& pGeom);
};
#endif // UTILITY_H
//------------------------------------------------------------------
