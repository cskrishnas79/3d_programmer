// ------------------------------------------------------------------
//
// Object Utility Declaration
//
//------------------------------------------------------------------
#ifndef OBJECT_UTILS_H
#define OBJECT_UTILS_H

#include "data\data.h"
#include "data\geom.h"
#include "data\topo.h"

class ObjectUtils
{
public:

	static bool GetPosAndDirection(const std::shared_ptr<data::Entity>& pPath, const float& interval,
							const float& speed,	double prevPos[3], double nextPos[3], double dir[3]);

private:

	static bool GetPosAndDirection(const std::shared_ptr<data::Geom>& pGeom, const float& interval,
							const float& speed,	double prevPos[3], double nextPos[3], double dir[3]);
};
#endif // OBJECT_UTILS_H
//------------------------------------------------------------------