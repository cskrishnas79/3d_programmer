//------------------------------------------------------------------
//
// Object Declaration
//
//------------------------------------------------------------------
#ifndef OBJECT_H
#define OBJECT_H

#include "data\data.h"
#include "data\geom.h"
#include "data\topo.h"
#include "data\display.h"
#include "utils\defines.h"

class Object
{
public:
	Object(std::shared_ptr<data::Topo>& pBody);
	~Object();

	bool Initialize();
	void AddObjectPath(std::shared_ptr<data::Entity>& pPath);
	bool Update();
	inline void SetSpeed(float speed) { m_speed = speed; }

public:
	long m_objectId;										// store object id
	std::shared_ptr<data::Topo> m_objBody;					// stores object shape
	std::vector<std::shared_ptr<data::Entity> > m_objPaths; // stores object paths

private:

	float m_speed;
	double m_dimHalf[3]; // stores half width, depth and depth of the complete body
	double m_location[3];
	double m_direction[3];
};
#endif // OBJECT_H
//------------------------------------------------------------------