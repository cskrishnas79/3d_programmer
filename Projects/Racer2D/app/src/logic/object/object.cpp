//------------------------------------------------------------------
//
// Object Implementation
//
//------------------------------------------------------------------

#include "logic\object\object.h"
#include "logic\object\objectutils.h"

Object::Object(const std::shared_ptr<data::Topo>& pBody) : m_objectId(0), m_objBody(pBody), m_speed(0.0),
										m_interval(0.0), m_currPathIndex(0)
{
	m_location[0] = m_location[1] = m_location[2] = 0.0;
	m_direction[0] = m_direction[1] = m_direction[2] = 0.0;
	m_dimHalf[0] = m_dimHalf[1] = m_dimHalf[2] = 0.0;
}

Object::~Object()
{
	m_collisionTopo.clear();
}

bool Object::Initialize()
{
	if (m_objPaths.size() == 0)
		return false;

	// Get the bounding box of the body
	double min[3] = { 0.0,0.0,0.0 }, max[3] = { 0.0,0.0,0.0 };
	m_objBody->GetBoundingBox(min, max);
	m_objBody->ComputeEncloseBox();

	m_dimHalf[0] = (max[0] - min[0]) / 2;
	m_dimHalf[1] = (max[1] - min[1]) / 2;
	m_dimHalf[2] = (max[2] - min[2]) / 2;

	// find the cg of the body
	m_location[0] = min[0] + m_dimHalf[0];
	m_location[1] = min[1] + m_dimHalf[1];
	m_location[2] = min[2] + m_dimHalf[2];

	// reference axis for the body is x axis
	m_direction[0] = 1.0;
	m_direction[1] = 0.0;
	m_direction[2] = 0.0;

	double nextPos[3] = { 0.0,0.0,0.0 }, nextDir[3] = { 0.0,0.0,0.0 };
	std::shared_ptr<data::Entity>& pCurrPath = m_objPaths[m_currPathIndex];
	bool bRes = ObjectUtils::GetPosAndDirection(pCurrPath, m_interval, m_speed, m_location, nextPos, nextDir);
	if (bRes == true)
	{
		Vector v1(m_location), v2(nextPos);
		Vector displDir = (v2 - v1);
		const double* dir = displDir.get();

		Matrix trans;
		trans.translate(dir[0], (dir[1] + m_dimHalf[1]), (dir[2] + m_dimHalf[2]));
		m_objBody->Transform(trans);

		// Set the direction of the object
		UpdateOrientation(nextPos, nextDir);

		m_location[0] = nextPos[0];	m_location[1] = nextPos[1];	m_location[2] = nextPos[2];
		m_direction[0] = nextDir[0]; m_direction[1] = nextDir[1]; m_direction[2] = nextDir[2];
		// Increment the interval
		m_interval++;
	}
	return bRes;
}

void Object::AddObjectPath(const std::shared_ptr<data::Entity>& pPath)
{
	m_objPaths.push_back(pPath);
}

bool Object::Update()
{
	// First retain the state of the topo collided previously
	std::map<std::shared_ptr<data::Topo>, data::Display>::iterator it = m_collisionTopo.begin();
	for (; it != m_collisionTopo.end(); ++it)
	{
		const std::shared_ptr<data::Topo>& pTopo = (*it).first;
		data::Display& disply = (*it).second;
		pTopo->SetDisplay(disply);
	}
	m_collisionTopo.clear();

	bool bDirectionChanged = false;
	std::shared_ptr<data::Entity>& pCurrPath = m_objPaths[m_currPathIndex];
	double nextPos[3] = { 0.0,0.0,0.0 }, nextDir[3] = { 0.0,0.0,0.0 };
	bool bRes = ObjectUtils::GetPosAndDirection(pCurrPath, m_interval, m_speed, m_location, nextPos, nextDir);
	if (bRes == false)
	{
		unsigned int len = (unsigned int)m_objPaths.size();
		if (m_currPathIndex < len - 1)
		{
			m_interval = 0; bDirectionChanged = true;
			m_currPathIndex++;
		}
		else
		{
			m_interval = 0; bDirectionChanged = true;
			m_currPathIndex = 0;
		}

		std::shared_ptr<data::Entity>& pCurrPath = m_objPaths[m_currPathIndex];
		bRes = ObjectUtils::GetPosAndDirection(pCurrPath, m_interval, m_speed, m_location, nextPos, nextDir);
		if (bRes == false)
			return bRes;
	}

	Vector v1(m_location), v2(nextPos);
	Vector displDir = (v2 - v1);
	const double* dir = displDir.get();

	Matrix trans;
	trans.translate(dir[0], dir[1], dir[2]);
	m_objBody->Transform(trans);

	if (bDirectionChanged == true)
	{
		UpdateOrientation(nextPos, nextDir);
		bDirectionChanged = false;
	}

	m_location[0] = nextPos[0];	m_location[1] = nextPos[1];	m_location[2] = nextPos[2];
	m_direction[0] = nextDir[0]; m_direction[1] = nextDir[1]; m_direction[2] = nextDir[2];
	// Increment the interval
	m_interval++;
	return bRes;
}

void Object::UpdateOrientation(double nextPos[3], double nextDir[3])
{
	Vector v1(m_direction), v2(nextDir);
	double angle = v2.angle(v1);
	Vector cross = v1.cross(v2);
	Vector uCross = cross.normalize();
	double length = uCross.length();

	if (length > 0.0)
	{
		// before rotation first move the object to origin
		Matrix trans;
		trans.translate(-nextPos[0], -nextPos[1], -nextPos[2]);
		m_objBody->Transform(trans);

		// apply rotation
		Matrix rotate;
		const double* axis = uCross.get();
		if (axis[2] < 0)
			rotate.rotateZ(-angle);
		else
			rotate.rotateZ(angle);

		m_objBody->Transform(rotate);

		// now translate back
		Matrix backTrans;
		backTrans.translate(nextPos[0], nextPos[1], nextPos[2]);
		m_objBody->Transform(backTrans);
	}
}

void Object::AddCollideTopo(const std::shared_ptr<data::Topo>& pTopo)
{
	// if already there in the map just return
	std::map<std::shared_ptr<data::Topo>, data::Display>::iterator it = m_collisionTopo.find(pTopo);
	if (it != m_collisionTopo.end())
		return;

	m_collisionTopo.insert(std::pair<std::shared_ptr<data::Topo>, data::Display>(pTopo, pTopo->m_display));

	// Change the display of the collided topo
	data::Display disply;
	disply.m_color[0] = 0.0; disply.m_color[1] = 1.0; disply.m_color[2] = 0.0;
	disply.m_lineWidth = 2.0f;
	pTopo->SetDisplay(disply);
}