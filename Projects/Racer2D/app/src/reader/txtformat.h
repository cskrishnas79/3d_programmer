//------------------------------------------------------------------
//
// Text Format Declaration to read file and populate objects
//
//------------------------------------------------------------------
#ifndef TXT_FORMAT_H
#define TXT_FORMAT_H

#include "reader\format.h"

class TxtFormat : public Format
{
public:
	TxtFormat();
	~TxtFormat();
	bool GetObjects(const std::string& objFile, std::vector<std::shared_ptr<Object> >& objects) override;

private:

	std::shared_ptr<Object> GetObject(std::ifstream& file);
	std::shared_ptr<data::Topo> GetAssembly(std::ifstream& file);
	std::shared_ptr<data::Topo> GetPart(std::ifstream& file);
	std::shared_ptr<data::Geom> GetGeom(std::ifstream& file);

	bool AddObjectPath(std::ifstream& file, std::shared_ptr<Object>& pObject);
	bool AddComponent(std::ifstream& file, std::shared_ptr<data::Assembly>& pAssembly);
	void SetDisplayAttributes(std::ifstream& file, std::shared_ptr<data::Topo>& pTopo);
	void SetTransformation(std::ifstream& file, std::shared_ptr<data::Part>& pTopo);
};
#endif // TXT_FORMAT_H
//------------------------------------------------------------------