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
	Object(const std::shared_ptr<data::Topo>& pBody);
	~Object();

	bool Initialize();
	void AddObjectPath(const std::shared_ptr<data::Entity>& pPath);
	bool Update();
	inline void SetSpeed(float speed) { m_speed = speed; }
	void AddCollideTopo(const std::shared_ptr<data::Topo>& pTopo);

private:
	void UpdateOrientation(double nextPos[3], double nextDir[3]);

public:
	long m_objectId;										// store object id
	std::shared_ptr<data::Topo> m_objBody;					// stores object shape
	std::vector<std::shared_ptr<data::Entity> > m_objPaths; // stores object paths

private:
	unsigned int m_currPathIndex;
	float m_speed;
	float m_interval;
	double m_dimHalf[3]; // stores half width, height and depth of the complete body
	double m_location[3];
	double m_direction[3];

	// stores the previous state of the topos before collision
	std::map<std::shared_ptr<data::Topo>, data::Display> m_collisionTopo;
};
#endif // OBJECT_H
//------------------------------------------------------------------