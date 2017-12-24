//------------------------------------------------------------------
//
// Logic Implementation
//
//------------------------------------------------------------------
#include "logic\logic.h"

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
	std::vector<std::shared_ptr<data::Entity> > entities;
	
	if (m_viewer.expired())
		return false;
	return m_viewer.lock()->View(entities);
}

bool Logic::Update()
{
	if (Simulate() == false)
		return false;

	std::vector<std::shared_ptr<data::Entity> > entities;

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