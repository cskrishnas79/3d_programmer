//
// Racer2D.cpp : Defines the entry point for the racer application.
//
//
//-----------------------------------------------------------------------------
#include <iostream>
#include "engine\engine.h"

#define ERROR_MSG "\nError starting application.\nUsage: program objectfile viewfile[optional]"

void PrintMessage(ReturnCode retCode)
{
	switch (retCode)
	{
	case ReturnCode::RETURN_FAILURE:
	{
		std::cout << ERROR_MSG << std::endl;
		break;
	}
	case ReturnCode::RETURN_EXECEPTION:
	{
		std::cout << "\nExeception Occurred" << std::endl;
		break;
	}
	case ReturnCode::RETURN_INITIALIZE_LOGIC_ERROR:
	{
		std::cout << "\nFailed to Initialize Logic component" << std::endl;
		break;
	}
	case ReturnCode::RETURN_INITIALIZE_VIEWER_ERROR:
	{
		std::cout << "\nFailed to Initialize Viewer component" << std::endl;
		break;
	}
	case ReturnCode::RETURN_READING_VIEWER_OPT_ERROR:
	{
		std::cout << "\nFailed to Read Viewer Options" << std::endl;
		break;
	}
	default:
		break;
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		PrintMessage(ReturnCode::RETURN_FAILURE);
		return -1;
	}

	Engine engine;

	ReturnCode retCode = engine.Initialize(argc, argv);
	if (retCode != ReturnCode::RETURN_SUCCESS)
	{
		PrintMessage(retCode);
		return -1;
	}

	retCode = engine.Play();
	if (retCode != ReturnCode::RETURN_SUCCESS)
	{
		PrintMessage(retCode);
		return -1;
	}
	return 0;
}

