// ------------------------------------------------------------------
//
// Reader Declaration
//
//------------------------------------------------------------------
#ifndef READER_H
#define READER_H

#include "logic\object\object.h"

class Reader
{
public:

	Reader();
	~Reader();

	bool ReadObjects(const std::string& objFile, std::vector<std::shared_ptr<Object> >& objects);
};
#endif // READER_H
//------------------------------------------------------------------