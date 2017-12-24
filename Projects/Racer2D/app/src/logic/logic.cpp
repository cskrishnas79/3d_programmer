//------------------------------------------------------------------
//
// Logic Implementation
//
//------------------------------------------------------------------
#include "logic\logic.h"
#include "reader\reader.h"

Logic::Logic()
{
}

Logic::~Logic()
{
}

bool Logic::Simulate()
{
	return true;
}

// Start Interface methods implementation
bool Logic::Initialize(const std::string& objFile)
{
	Reader objReader;
	if (objReader.ReadObjects(objFile, m_objects) == false)
		return false;

	std::vector<std::shared_ptr<data::Entity> > entities;
	for (auto obj : m_objects)
	{
		obj->Initialize();

		entities.push_back(obj->m_objBody);
#ifdef _DEBUG
		entities.push_back(obj->m_objBody->m_boxGeom);
#endif
		for (auto path : obj->m_objPaths)
			entities.push_back(path);
	}
	
	if (m_viewer.expired())
		return false;
	return m_viewer.lock()->View(entities);
}

bool Logic::Update()
{
	if (Simulate() == false)
		return false;

	std::vector<std::shared_ptr<data::Entity> > entities;
	for (auto obj : m_objects)
	{
		entities.push_back(obj->m_objBody);
#ifdef _DEBUG
		entities.push_back(obj->m_objBody->m_boxGeom);
#endif
		for (auto path : obj->m_objPaths)
			entities.push_back(path);
	}

	if (m_viewer.expired())
		return false;
	return m_viewer.lock()->Update(entities);
}

bool Logic::RegisterViewer(const std::shared_ptr<IViewer>& pViewer)
{
	m_viewer = pViewer;
	return true;
}
// End Interface methods implementation