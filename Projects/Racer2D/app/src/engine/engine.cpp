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

ReturnCode Engine::Initialize(int argc, char* argv[])
{
	ReturnCode retCode = ReturnCode::RETURN_SUCCESS;
	try
	{
		m_viewer = std::make_shared<Viewer>();
		m_logic = std::make_shared<Logic>();

		m_viewer->RegisterLogic(m_logic);
		m_logic->RegisterViewer(m_viewer);

		ViewerOpts opts;
		// if more than two argument, the third argument is the viewer option file else set default options
		if (argc > 2)
		{
			std::string viewFile = argv[2];
			bool bRes = opts.ReadOptions(viewFile);
			if (bRes == false)
				return ReturnCode::RETURN_READING_VIEWER_OPT_ERROR;
		}

		bool bRes = m_viewer->Initialize(opts);
		if (bRes == false)
			return ReturnCode::RETURN_INITIALIZE_VIEWER_ERROR;

		// the second argument is the game object file
		std::string objFile = argv[1];
		bRes = m_logic->Initialize(objFile);
		if (bRes == false)
			return ReturnCode::RETURN_INITIALIZE_LOGIC_ERROR;
	}
	catch (...)
	{
		retCode = ReturnCode::RETURN_EXECEPTION;
	}
	return retCode;
}

ReturnCode Engine::Play()
{
	ReturnCode retCode = ReturnCode::RETURN_SUCCESS;
	try
	{
		bool bRes = m_viewer->Play();
		if (bRes == false)
			retCode = ReturnCode::RETURN_FAILURE;
	}
	catch (...)
	{
		retCode = ReturnCode::RETURN_EXECEPTION;
	}
	return retCode;
}
