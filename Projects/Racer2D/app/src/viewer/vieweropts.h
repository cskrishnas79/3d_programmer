//------------------------------------------------------------------
//
// Viewer Options
//
//------------------------------------------------------------------
#ifndef VIEWER_OPT_H
#define VIEWER_OPT_H

#include <string>
#include <fstream>

class ViewerOpts
{
public:

	ViewerOpts();
	~ViewerOpts();

	bool ReadOptions(const std::string& optFile);

private:

	bool ReadWindowOptions(std::ifstream& file);

public:
	int m_window_width;
	int m_window_height;
	int m_intial_pos[2];
	float m_backColor[4] = { 1.0,1.0,1.0,1.0 };
	std::string m_viewName;
};
#endif // VIEWER_OPT_H
//------------------------------------------------------------------