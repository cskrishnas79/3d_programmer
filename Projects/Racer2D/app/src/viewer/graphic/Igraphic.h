//------------------------------------------------------------------
//
// Graphic Interface
//
//------------------------------------------------------------------
#ifndef IGRAPHIC_H
#define IGRAPHIC_H

#include "viewer\viewer.h"

class IGraphic
{
public:
	IGraphic(Viewer* pViewer) : m_pViewer(pViewer) {}
	virtual ~IGraphic() {}

	virtual bool Initialize(const ViewerOpts& vOptions) = 0;
	virtual bool Show() = 0;
	virtual bool AddToGraphic(const std::vector<std::shared_ptr<data::Entity> >& objs) = 0;
	virtual bool UpdateGraphic(const std::vector<std::shared_ptr<data::Entity> >& objs) = 0;

protected:
	Viewer* m_pViewer;
};
#endif // IGRAPHIC_H
//------------------------------------------------------------------