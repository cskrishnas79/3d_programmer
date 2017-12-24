//------------------------------------------------------------------
//
// Display class Declaration (Data type for holding display attributes)
//
//------------------------------------------------------------------
#ifndef DISPLAY_H
#define DISPLAY_H

namespace data
{
	enum class DisplayType
	{
		FILL_TYPE,
		LINE_TYPE,
		POINT_TYPE
	};

	class Display
	{
	public:
		Display();
		virtual ~Display();
		Display(const Display& disply);
		Display& operator=(const Display& disply);

	public:
		double m_color[3];
		float m_lineWidth;
		DisplayType m_mode;
	};
}
#endif //DISPLAY_H
//------------------------------------------------------------------