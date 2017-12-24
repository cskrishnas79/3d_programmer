//------------------------------------------------------------------
//
// Format Base class Declaration
//
//------------------------------------------------------------------
#ifndef FORMAT_H
#define FORMAT_H

#include "logic\object\object.h"

class Format
{
public:
	virtual bool GetObjects(const std::string& objFile, std::vector<std::shared_ptr<Object> >& objects) = 0;
};
#endif // FORMAT_H
//------------------------------------------------------------------