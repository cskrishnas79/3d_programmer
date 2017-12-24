//------------------------------------------------------------------
//
// Utility class Implementation
//
//------------------------------------------------------------------
#include "data\utility.h"

std::shared_ptr<data::Geom> Utility::CopyGeom(const std::shared_ptr<data::Geom>& pGeom)
{
	std::shared_ptr<data::Geom> pCloneGeom(pGeom->Clone());
	return pCloneGeom;
}