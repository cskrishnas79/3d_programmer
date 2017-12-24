//------------------------------------------------------------------
//
// Viewer to wrap the implementation of display
//
//------------------------------------------------------------------
#include "viewer\viewer.h"
#include "viewer\graphic\glgraphic.h"

Viewer::Viewer()
{
}

Viewer::~Viewer()
{
}

// Start Interface methods implementation
bool Viewer::Initialize(const ViewerOpts& vOptions)
{
	// Create graphic object and initialize it
	m_pGraphicObj = std::make_shared<GLGraphic>(this);
	if (m_pGraphicObj == nullptr)
		return false;

	bool bRes = m_pGraphicObj->Initialize(vOptions);
	return bRes;
}

bool Viewer::Play()
{
	bool bRes = m_pGraphicObj->Show();
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
	bool bRes = m_pGraphicObj->AddToGraphic(objs);
	return bRes;
}

bool Viewer::Update(const std::vector<std::shared_ptr<data::Entity> >& objs)
{
	bool bRes = m_pGraphicObj->UpdateGraphic(objs);
	return bRes;
}
// End Interface methods implementation