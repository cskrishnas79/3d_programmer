//------------------------------------------------------------------
//
// Logic Interface
//
//------------------------------------------------------------------
#ifndef ILOGIC_H
#define ILOGIC_H

#include "data\data.h"

class IViewer;
class ILogic
{
public:
   
    virtual bool Initialize(const std::string& objFile) = 0;
	virtual bool Update() = 0;	
	virtual bool RegisterViewer(const std::shared_ptr<IViewer>& pViewer) = 0;
};
#endif // ILOGIC_H
//------------------------------------------------------------------