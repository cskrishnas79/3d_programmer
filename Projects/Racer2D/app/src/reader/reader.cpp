//------------------------------------------------------------------
//
// Reader Implementation
//
//------------------------------------------------------------------
#include "reader\reader.h"
#include "reader\txtformat.h"

Reader::Reader()
{
}

Reader::~Reader()
{
}

bool Reader::ReadObjects(const std::string& objFile, std::vector<std::shared_ptr<Object> >& objects)
{
	bool bRes = false;
	if (objFile.empty())
		return bRes;

	size_t pos = objFile.rfind(DOT);
	std::string ext = objFile.substr(pos + 1);
	if (ext == TXT)
	{
		TxtFormat fileFormat;
		bRes = fileFormat.GetObjects(objFile, objects);
	}

	return bRes;
}