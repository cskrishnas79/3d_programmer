// ------------------------------------------------------------------
//
// Utility Implementation
//
//------------------------------------------------------------------
#include <cstdlib>
#include <algorithm>
#include "utils\utils.h"

void StrUtils::GetValues(std::string& line, double* pValues)
{
	std::string::size_type sz;
	pValues[0] = std::stod(line, &sz);
	line = line.substr(sz);
	pValues[1] = std::stod(line, &sz);
	pValues[2] = std::stod(line.substr(sz));
}

void StrUtils::GetLine(std::ifstream& file, std::string& line, std::string str)
{
	getline(file, line);
	RemoveFromString(line, str);
}

void StrUtils::RemoveFromString(std::string& str, std::string& strToRemove)
{
	int len = (int)strToRemove.length();
	for (int i = 0; i < len; ++i)
	{
		str.erase(remove(str.begin(), str.end(), strToRemove[i]), str.end());
	}
}