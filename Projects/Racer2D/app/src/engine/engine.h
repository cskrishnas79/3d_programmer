// ------------------------------------------------------------------
//
// Engine Declaration
//
//------------------------------------------------------------------
#ifndef ENGINE_H
#define ENGINE_H

#include "logic\Ilogic.h"
#include "viewer\Iviewer.h"

enum class ReturnCode
{
	RETURN_SUCCESS = 0,
	RETURN_FAILURE,
	RETURN_EXECEPTION,
	RETURN_INITIALIZE_LOGIC_ERROR,
	RETURN_INITIALIZE_VIEWER_ERROR,
	RETURN_READING_VIEWER_OPT_ERROR
};

class Engine
{
public:

	Engine();
	~Engine();

	ReturnCode Initialize(int argc, char* argv[]);
	ReturnCode Play();

private:
	std::shared_ptr<IViewer> m_viewer;
	std::shared_ptr<ILogic> m_logic;
};
#endif // ENGINE_H
//------------------------------------------------------------------