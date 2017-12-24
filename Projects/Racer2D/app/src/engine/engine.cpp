//------------------------------------------------------------------
//
// Engine Implementation
//
//------------------------------------------------------------------
#include "engine.h"
#include "viewer\viewer.h"
#include "logic\logic.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

bool Engine::Initialize(int argc, char* argv[])
{
	bool bRes = false;
	m_viewer = std::make_shared<Viewer>();
	m_logic = std::make_shared<Logic>();

	m_viewer->RegisterLogic(m_logic);
	m_logic->RegisterViewer(m_viewer);

	ViewerOpts opts;

	// if more than two argument, the third argument is the viewer option file else set default options
	if (argc > 2)
	{
		std::string viewFile = argv[2];
		bRes = opts.ReadOptions(viewFile);
		if (bRes == false)
			return bRes;
	}

	bRes = m_viewer->Initialize(opts);
	if (bRes == false)
		return bRes;

	// the second argument is the game object file
	std::string objFile = argv[1];
	bRes = m_logic->Initialize(objFile);
	if (bRes == false)
		return bRes;
	return true;
}

bool Engine::Play()
{
	bool bRes = m_viewer->Play();
	return bRes;
}
