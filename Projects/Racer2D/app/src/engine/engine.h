// ------------------------------------------------------------------
//
// Engine Declaration
//
//------------------------------------------------------------------
#ifndef ENGINE_H
#define ENGINE_H

#include "logic\Ilogic.h"
#include "viewer\Iviewer.h"

class Engine
{
public:

	Engine();
	~Engine();

	bool Initialize(int argc, char* argv[]);
	bool Play();

private:
	std::shared_ptr<IViewer> m_viewer;
	std::shared_ptr<ILogic> m_logic;
};
#endif // ENGINE_H
//------------------------------------------------------------------