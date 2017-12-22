//------------------------------------------------------------------
//
// Viewer Interface
//
//------------------------------------------------------------------
#ifndef IVIEWER_H
#define IVIEWER_H

#include "data\data.h"
#include "logic\Ilogic.h"

class IViewer
{
public:
   
    virtual bool Initialize() = 0;
	virtual bool Play() = 0;
	virtual bool View(std::vector<std::shared_ptr<data::Entity> >& objs) = 0;
	virtual bool Update(std::vector<std::shared_ptr<data::Entity> >& objs) = 0;
	virtual bool RegisterLogic(std::shared_ptr<ILogic>& pLogic) = 0;
};
#endif // IVIEWER_H
//------------------------------------------------------------------