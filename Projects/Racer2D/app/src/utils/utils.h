// ------------------------------------------------------------------
//
// Utility Declaration
//
//------------------------------------------------------------------
#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <string>
#include "utils\defines.h"

class StrUtils
{
public:

	static void GetLine(std::ifstream& file, std::string& line, std::string str = DELIMITER_TAG);
	static void GetValues(std::string& line, double* pValues);
	static void RemoveFromString(std::string& str, std::string& strToRemove);
};
#endif // UTILS_H
//------------------------------------------------------------------