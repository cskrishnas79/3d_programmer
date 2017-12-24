//------------------------------------------------------------------
//
// Logic Declaration
//
//------------------------------------------------------------------
#ifndef LOGIC_H
#define LOGIC_H

#include "viewer\Iviewer.h"

class Logic : public ILogic
{
public:

	Logic();
	~Logic();

	bool Initialize(const std::string& objFile) override;
	bool Update() override;
	bool RegisterViewer(const std::shared_ptr<IViewer>& pViewer) override;

private:
	bool Simulate();

private:
	std::weak_ptr<IViewer> m_viewer;
};
#endif // LOGIC_H
//------------------------------------------------------------------