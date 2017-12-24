//------------------------------------------------------------------
//
// Viewer Interface
//
//------------------------------------------------------------------
#ifndef IVIEWER_H
#define IVIEWER_H

#include "data\data.h"
#include "logic\Ilogic.h"
#include "viewer\vieweropts.h"

class IViewer
{
public:
   
    virtual bool Initialize(const ViewerOpts& vOptions) = 0;
	virtual bool Play() = 0;
	virtual bool View(const std::vector<std::shared_ptr<data::Entity> >& objs) = 0;
	virtual bool Update(const std::vector<std::shared_ptr<data::Entity> >& objs) = 0;
	virtual bool RegisterLogic(const std::shared_ptr<ILogic>& pLogic) = 0;
};
#endif // IVIEWER_H
//------------------------------------------------------------------