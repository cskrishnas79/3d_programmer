//------------------------------------------------------------------
//
// Text Format Implementation to read file and populate objects
//
//------------------------------------------------------------------
#include "reader\txtformat.h"
#include "utils\utils.h"
#include "utils\defines.h"

static long modelId = 0;

TxtFormat::TxtFormat()
{
	modelId = 0;
}

TxtFormat::~TxtFormat()
{
	modelId = 0;
}

std::shared_ptr<data::Topo> TxtFormat::GetAssembly(std::ifstream& file)
{
	std::shared_ptr<data::Topo> pTopo;

	std::string buffer(EMPTY_TAG);
	StrUtils::GetLine(file, buffer);
	if (buffer == OPEN_TAG)
	{
		std::shared_ptr<data::Assembly> pAssembly = std::make_shared<data::Assembly>();
		// read assembly attributes and components
		do
		{
			StrUtils::GetLine(file, buffer);
			if (buffer == NAME)
			{
				std::string name(EMPTY_TAG);
				StrUtils::GetLine(file, name);
				pAssembly->m_name = name;
			}
			else if (buffer == COMPONENT)
			{
				bool bRes = AddComponent(file, pAssembly);
			}
		} while (buffer != CLOSE_TAG); // close of assembly

		if (pAssembly != nullptr)
			pTopo = std::dynamic_pointer_cast<data::Topo>(pAssembly);
	}
	return pTopo;
}

bool TxtFormat::AddComponent(std::ifstream& file, std::shared_ptr<data::Assembly>& pAssembly)
{
	bool bRes = false;

	std::string buffer(EMPTY_TAG);
	StrUtils::GetLine(file, buffer);
	if (buffer == OPEN_TAG)
	{
		do
		{
			StrUtils::GetLine(file, buffer);
			if (buffer == PART)
			{
				std::shared_ptr<data::Topo> pTopo = GetPart(file);
				if (pTopo != nullptr)
				{
					pTopo->m_id = modelId;
					std::shared_ptr<data::Part> pPart = std::dynamic_pointer_cast<data::Part>(pTopo);
					pAssembly->m_components.push_back(pPart);
				}
			}
		} while (buffer != CLOSE_TAG); // close of component
	}
	return bRes;
}

std::shared_ptr<data::Topo> TxtFormat::GetPart(std::ifstream& file)
{
	std::shared_ptr<data::Topo> pTopo;

	std::string buffer(EMPTY_TAG);
	StrUtils::GetLine(file, buffer);
	if (buffer == OPEN_TAG)
	{
		std::shared_ptr<data::Part> pPart;
		std::string name(EMPTY_TAG);
		do
		{
			StrUtils::GetLine(file, buffer);
			if (buffer == NAME)
			{
				StrUtils::GetLine(file, name);
			}
			else if (buffer == SHAPE)
			{
				std::shared_ptr<data::Geom> pGeom = GetGeom(file);
				if (pGeom != nullptr)
				{
					pPart = std::make_shared<data::Part>(pGeom);
					pPart->m_name = name;
				}
			}
			else if (buffer == TRANSFORMATION)
			{
				SetTransformation(file, pPart);
			}
			else if (buffer == DISPLAY)
			{
				std::shared_ptr<data::Topo> pTopo = std::dynamic_pointer_cast<data::Topo>(pPart);
				SetDisplayAttributes(file, pTopo);
			}

		} while (buffer != CLOSE_TAG); // close of part

		if (pPart != nullptr)
			pTopo = std::dynamic_pointer_cast<data::Topo>(pPart);
	}
	return pTopo;
}

std::shared_ptr<data::Geom> TxtFormat::GetGeom(std::ifstream& file)
{
	std::shared_ptr<data::Geom> pGeom;

	std::string buffer(EMPTY_TAG);
	StrUtils::GetLine(file, buffer);
	if (buffer == OPEN_TAG)
	{
		do
		{
			StrUtils::GetLine(file, buffer);
			if (buffer == POINT)
			{
				std::string str(EMPTY_TAG);
				StrUtils::GetLine(file, str);
				double point[3] = { 0.0,0.0,0.0 };
				StrUtils::GetValues(str, point);

				pGeom = std::make_shared<data::Point>(point);
			}
			else if (buffer == LINE)
			{
				double start[3] = { 0.0,0.0,0.0 }, end[3] = { 0.0,0.0,0.0 };
				int numParam = 2;
				for (int i = 0; i < numParam; ++i)
				{
					StrUtils::GetLine(file, buffer);
					if (buffer == START)
					{
						std::string str(EMPTY_TAG);
						StrUtils::GetLine(file, str);
						StrUtils::GetValues(str, start);
					}
					else if (buffer == END)
					{
						std::string str(EMPTY_TAG);
						StrUtils::GetLine(file, str);
						StrUtils::GetValues(str, end);
					}
				}
				pGeom = std::make_shared<data::Line>(start, end);
			}
			else if (buffer == RECTANGLE)
			{
				double center[3] = { 0.0,0.0,0.0 };
				double width = 0.0, height = 0.0;
				int numParam = 3;
				for (int i = 0; i < numParam; ++i)
				{
					StrUtils::GetLine(file, buffer);
					if (buffer == CENTER)
					{
						std::string cen(EMPTY_TAG);
						StrUtils::GetLine(file, cen);
						StrUtils::GetValues(cen, center);
					}
					else if (buffer == WIDTH)
					{
						std::string w(EMPTY_TAG);
						StrUtils::GetLine(file, w);

						std::string::size_type sz;
						width = std::stod(w, &sz);
					}
					else if (buffer == HEIGHT)
					{
						std::string h(EMPTY_TAG);
						StrUtils::GetLine(file, h);

						std::string::size_type sz;
						height = std::stod(h, &sz);
					}
				}

				pGeom = std::make_shared<data::Rectangle>(center, width, height);
			}
			else if (buffer == CIRCLE)
			{
				double center[3] = { 0.0,0.0,0.0 };
				double radius = 0.0;
				int numParam = 2;
				for (int i = 0; i < numParam; ++i)
				{
					StrUtils::GetLine(file, buffer);
					if (buffer == CENTER)
					{
						std::string cen(EMPTY_TAG);
						StrUtils::GetLine(file, cen);
						StrUtils::GetValues(cen, center);
					}
					else if (buffer == RADIUS)
					{
						std::string r(EMPTY_TAG);
						StrUtils::GetLine(file, r);

						std::string::size_type sz;
						radius = std::stod(r, &sz);
					}
				}
				pGeom = std::make_shared<data::Circle>(center, radius);
			}
			else if (buffer == POLYGON)
			{
				StrUtils::GetLine(file, buffer);

				std::string::size_type sz;
				int numPoints = std::stoi(buffer, &sz);
				if (numPoints > 1)
				{
					std::shared_ptr<data::Polygon> pPolygon = std::make_shared<data::Polygon>();
					for (int i = 0; i < numPoints; ++i)
					{
						std::string str(EMPTY_TAG);
						StrUtils::GetLine(file, str);

						double point[3] = { 0.0,0.0,0.0 };
						StrUtils::GetValues(str, point);

						pPolygon->m_points.push_back(std::make_shared<data::Point>(point));
					}

					pGeom = std::dynamic_pointer_cast<data::Geom>(pPolygon);
				}
			}
		} while (buffer != CLOSE_TAG);  // close of shape/geometry
	}
	return pGeom;
}

void TxtFormat::SetTransformation(std::ifstream& file, std::shared_ptr<data::Part>& pPart)
{
	std::string buffer(EMPTY_TAG);
	StrUtils::GetLine(file, buffer);
	if (buffer == OPEN_TAG && pPart != nullptr)
	{
		do
		{
			StrUtils::GetLine(file, buffer);
			if (buffer == TRANSLATE)
			{
				std::string str(EMPTY_TAG);
				StrUtils::GetLine(file, str);

				double val[3] = { 0.0,0.0,0.0 };
				StrUtils::GetValues(str, val);

				Matrix trans;
				trans.translate(val[0], val[1], val[2]);
				pPart->Transform(trans);
			}
			else if (buffer == ROTATE)
			{
				std::string str(EMPTY_TAG);
				StrUtils::GetLine(file, str);

				double rotAngleZ = 0.0;
				std::string::size_type sz;
				rotAngleZ = std::stof(str, &sz);

				// convert from degree to radian
				constexpr double fact = 3.141592653589 / 180;
				rotAngleZ *= fact;

				Matrix rotate;
				rotate.rotateZ(rotAngleZ);
				pPart->Transform(rotate);
			}
		} while (buffer != CLOSE_TAG);  // close of transformation
	}
}

void TxtFormat::SetDisplayAttributes(std::ifstream& file, std::shared_ptr<data::Topo>& pTopo)
{
	std::string buffer(EMPTY_TAG);
	StrUtils::GetLine(file, buffer);
	if (buffer == OPEN_TAG && pTopo != nullptr)
	{
		data::Display disply;
		do
		{
			StrUtils::GetLine(file, buffer);
			if (buffer == COLOR)
			{
				std::string str(EMPTY_TAG);
				StrUtils::GetLine(file, str);
				StrUtils::GetValues(str, disply.m_color);
			}
			else if (buffer == LINEWIDTH)
			{
				std::string str(EMPTY_TAG);
				StrUtils::GetLine(file, str);

				std::string::size_type sz;
				disply.m_lineWidth = std::stof(str, &sz);
			}
			else if (buffer == POINTSIZE)
			{
				std::string str(EMPTY_TAG);
				StrUtils::GetLine(file, str);

				std::string::size_type sz;
				disply.m_pointSize = std::stof(str, &sz);
			}
			else if (buffer == POLYGONMODE)
			{
				std::string str(EMPTY_TAG);
				StrUtils::GetLine(file, str);

				if (str == LINEMODE)
					disply.m_mode = data::DisplayType::DISPLY_LINE;
				else if (str == FILLMODE)
					disply.m_mode = data::DisplayType::DISPLY_FILL;
				else if (str == POINTMODE)
					disply.m_mode = data::DisplayType::DISPLY_POINT;
			}
		} while (buffer != CLOSE_TAG);  // close of display attributes

		pTopo->SetDisplay(disply);
	}
}

bool TxtFormat::AddObjectPath(std::ifstream& file, std::shared_ptr<Object>& pObject)
{
	bool bRes = false;

	std::string buffer(EMPTY_TAG);
	StrUtils::GetLine(file, buffer);
	if (buffer == OPEN_TAG)
	{
		do
		{
			StrUtils::GetLine(file, buffer);
			if (buffer == PART)
			{
				std::shared_ptr<data::Topo> pTopo = GetPart(file);
				if (pTopo != nullptr)
				{
					pTopo->m_id = modelId;
					std::shared_ptr<data::Entity> pPath = std::dynamic_pointer_cast<data::Entity>(pTopo);
					pObject->AddObjectPath(pPath);
					bRes = true;
				}
			}
		} while (buffer != CLOSE_TAG); // close of Path
	}
	return bRes;
}

std::shared_ptr<Object> TxtFormat::GetObject(std::ifstream& file)
{
	std::shared_ptr<Object> pObj;

	std::string buffer(EMPTY_TAG);
	StrUtils::GetLine(file, buffer);
	if (buffer == OPEN_TAG)
	{
		//create object based on assembly/part and than add path to the object
		do
		{
			StrUtils::GetLine(file, buffer);
			if (buffer == ASSEMBLY)
			{
				std::shared_ptr<data::Topo> pTopo = GetAssembly(file);
				if (pTopo != nullptr)
				{
					pTopo->m_id = modelId;
					pObj = std::make_shared<Object>(pTopo);
				}
			}
			else if (buffer == PART)
			{
				std::shared_ptr<data::Topo> pTopo = GetPart(file);
				if (pTopo != nullptr)
				{
					pTopo->m_id = modelId;
					pObj = std::make_shared<Object>(pTopo);
				}
			}
			else if (buffer == SPEED && pObj != nullptr)
			{
				std::string str(EMPTY_TAG);
				StrUtils::GetLine(file, str);

				std::string::size_type sz;
				float speed = std::stof(str, &sz);
				pObj->SetSpeed(speed);
			}
			else if (buffer == PATH && pObj != nullptr)
			{
				AddObjectPath(file, pObj);
			}
		} while (buffer != CLOSE_TAG);
	}
	return pObj;
}

bool TxtFormat::GetObjects(const std::string& objFile, std::vector<std::shared_ptr<Object> >& objects)
{
	bool bRes = false;
	std::ifstream file(objFile);
	if (!file)
		return bRes;
	do
	{
		std::string buffer(EMPTY_TAG);
		StrUtils::GetLine(file, buffer);

		if (buffer == OBJECTS)
		{
			StrUtils::GetLine(file, buffer);
			std::string::size_type sz;
			int numObjs = std::stoi(buffer, &sz);

			for (int i = 0; i < numObjs; ++i)
			{
				std::string buffer(EMPTY_TAG);
				StrUtils::GetLine(file, buffer);
				if (buffer != OBJECT)
					continue;

				modelId++;
				std::shared_ptr<Object> pObj = GetObject(file);
				if (pObj != nullptr)
				{
					objects.push_back(pObj);
					pObj->m_objectId = modelId;
					bRes = true;
				}
			} // end of object
		} // end of objects

	} while (!file.eof());

	file.close();
	return bRes;
}