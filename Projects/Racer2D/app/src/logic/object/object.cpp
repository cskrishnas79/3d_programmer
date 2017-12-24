//------------------------------------------------------------------
//
// Object Implementation
//
//------------------------------------------------------------------

#include "logic\object\object.h"

Object::Object(std::shared_ptr<data::Topo>& pBody) : m_objectId(0), m_objBody(pBody), m_speed(0.0)
{
	m_location[0] = m_location[1] = m_location[2] = 0.0;
	m_direction[0] = m_direction[1] = m_direction[2] = 0.0;
	m_dimHalf[0] = m_dimHalf[1] = m_dimHalf[2] = 0.0;
}

Object::~Object()
{
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

	return true;
}

void Object::AddObjectPath(std::shared_ptr<data::Entity>& pPath)
{
	m_objPaths.push_back(pPath);
}

bool Object::Update()
{
	return true;
}