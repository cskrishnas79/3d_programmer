//------------------------------------------------------------------
//
// Viewer to wrap the implementation of display
//
//------------------------------------------------------------------
#ifndef VIEWER_H
#define VIEWER_H

#include "viewer\Iviewer.h"

class IGraphic;
class Viewer : public IViewer
{
public:
	Viewer();
	~Viewer();

	bool Initialize(const ViewerOpts& vOptions) override;
	bool Play() override;
	bool View(const std::vector<std::shared_ptr<data::Entity> >& objs) override;
	bool Update(const std::vector<std::shared_ptr<data::Entity> >& objs) override;
	bool RegisterLogic(const std::shared_ptr<ILogic>& pLogic) override;
	bool UpdateLogic();

private:

	std::weak_ptr<ILogic> m_pLogic;
	std::shared_ptr<IGraphic> m_pGraphicObj;
};
#endif // VIEWER_H
//------------------------------------------------------------------