//
// Racer2D.cpp : Defines the entry point for the racer application.
//
//
//-----------------------------------------------------------------------------
#include <iostream>
#include "engine\engine.h"

#define ERROR_MSG "\n Error starting application.\n Usage: program objectfile viewfile[optional]"

int main(int argc, char *argv[])
{
	if (argc < 1)
	{
		// Print usage message
		std::cout << ERROR_MSG << std::endl;
		return -1;
	}

	Engine engine;

	bool bRes = engine.Initialize(argc, argv);
	if (bRes == false)
	{
		// Print usage message
		std::cout << ERROR_MSG << std::endl;
		return -1;
	}

	bRes = engine.Play();
    return 0;
}

