//------------------------------------------------------------------
//
// Display class Implementation (Data type for holding display attributes)
//
//------------------------------------------------------------------
#include "data\display.h"

namespace data
{
	Display::Display()
	{
		m_lineWidth = 1.0f;							 // default width
		m_mode		= DisplayType::DISPLY_LINE;		 // default is line
		m_color[0]	= m_color[1] = m_color[2] = 0.0; // default is black color
 	}

	Display::~Display()
	{
	}

	Display::Display(const Display& disply)
	{
		m_color[0]	= disply.m_color[0];
		m_color[1]	= disply.m_color[1];
		m_color[2]	= disply.m_color[2];
		m_lineWidth = disply.m_lineWidth;
		m_mode		= disply.m_mode;
	}

	Display& Display::operator=(const Display& disply)
	{
		m_color[0]	= disply.m_color[0];
		m_color[1]	= disply.m_color[1];
		m_color[2]	= disply.m_color[2];
		m_lineWidth = disply.m_lineWidth;
		m_mode		= disply.m_mode;
		return (*this);
	}
}