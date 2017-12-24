//------------------------------------------------------------------
//
// Viewer to wrap the implementation of display
//
//------------------------------------------------------------------
#include "viewer\viewer.h"

Viewer::Viewer()
{
}

Viewer::~Viewer()
{
}

// Start Interface methods implementation
bool Viewer::Initialize(const ViewerOpts& vOptions)
{
	bool bRes = false;
	return bRes;
}

bool Viewer::Play()
{
	bool bRes = false;
	return bRes;
}

bool Viewer::RegisterLogic(const std::shared_ptr<ILogic>& pLogic)
{
	m_pLogic = pLogic;
	return true;
}

bool Viewer::UpdateLogic()
{
	if (m_pLogic.expired())
		return false;
	return m_pLogic.lock()->Update();
}

bool Viewer::View(const std::vector<std::shared_ptr<data::Entity> >& objs)
{
	bool bRes = false;
	return bRes;
}

bool Viewer::Update(const std::vector<std::shared_ptr<data::Entity> >& objs)
{
	bool bRes = false;
	return bRes;
}
// End Interface methods implementation