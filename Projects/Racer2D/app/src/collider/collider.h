//------------------------------------------------------------------
//
// Collider Declaration (Finds collision between objects)
//
//------------------------------------------------------------------
#ifndef COLLIDER_H
#define COLLIDER_H

#include "logic\object\object.h"

class Collider
{
public:

	Collider();
	~Collider();

	bool FindCollision();
	void AddObject(const std::shared_ptr<Object>& pObj);

private:
	std::vector<std::shared_ptr<Object> > m_objects;

};
#endif // COLLIDER_H
//------------------------------------------------------------------