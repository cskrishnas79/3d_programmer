//------------------------------------------------------------------
//
// Viewer Options
//
//------------------------------------------------------------------
#include "viewer\vieweropts.h"

#define DOT				'.'
#define VIW				"viw"
#define VIEW_NAME		"Racer 2D"

#define OPEN_TAG		"{"
#define CLOSE_TAG		"}"
// Window attributes
#define WINDOW			"Window"
#define WINDOW_WIDTH	"Width"
#define WINDOW_HEIGHT	"Height"
#define WINDOW_TOP		"Top"
#define WINDOW_LEFT		"Left"
#define WINDOW_COLOR	"Color"

ViewerOpts::ViewerOpts() : m_window_width(1000), m_window_height(600), m_viewName(VIEW_NAME)
{
	m_intial_pos[0] = m_intial_pos[1] = 50;
}

ViewerOpts::~ViewerOpts()
{
}

bool ViewerOpts::ReadWindowOptions(std::ifstream& file)
{
	bool bRes = false;
	std::string buffer("");
	getline(file, buffer);

	if (buffer != OPEN_TAG)
		return bRes;

	do
	{
		getline(file, buffer);
		if (buffer == WINDOW_WIDTH)
		{
			std::string str("");
			getline(file, str);

			std::string::size_type sz;
			m_window_width = std::stoi(str, &sz);
		}
		else if (buffer == WINDOW_HEIGHT)
		{
			std::string str("");
			getline(file, str);

			std::string::size_type sz;
			m_window_height = std::stoi(str, &sz);
		}
		else if (buffer == WINDOW_TOP)
		{
			std::string str("");
			getline(file, str);

			std::string::size_type sz;
			m_intial_pos[1] = std::stoi(str, &sz);
		}
		else if (buffer == WINDOW_LEFT)
		{
			std::string str("");
			getline(file, str);

			std::string::size_type sz;
			m_intial_pos[0] = std::stoi(str, &sz);
		}
		else if (buffer == WINDOW_COLOR)
		{
			std::string str("");
			getline(file, str);

			std::string::size_type sz;
			m_backColor[0] = std::stof(str, &sz);		// R value
			str = str.substr(sz);
			m_backColor[1] = std::stof(str, &sz);		// G value
			m_backColor[2] = std::stof(str.substr(sz));	// B value
		}
	} while (buffer != CLOSE_TAG);  // close of window attributes

	return true;
}

bool ViewerOpts::ReadOptions(const std::string& optFile)
{
	bool bRes = false;
	if (optFile.empty())
		return bRes;

	size_t pos = optFile.rfind(DOT);
	std::string ext = optFile.substr(pos + 1);
	if (ext != VIW)
		return bRes;

	std::ifstream file(optFile);
	if (!file)
		return bRes;

	do
	{
		std::string buffer("");
		getline(file, buffer);

		if (buffer == WINDOW)
		{
			bRes = ReadWindowOptions(file);
		} // end of Window

	} while (!file.eof() && bRes != false);

	file.close();
	return bRes;
}