//------------------------------------------------------------------
//
// Graphic using freeglut for display
//
//------------------------------------------------------------------
#ifndef GL_GRAPHIC_H
#define GL_GRAPHIC_H

#include "viewer\graphic\Igraphic.h"
#include "viewer\graphic\globject.h"

class GLGraphic : public IGraphic
{
public:
	GLGraphic(const std::shared_ptr<Viewer>& pViewer);
	~GLGraphic();

	bool Initialize(const ViewerOpts& vOptions) override;
	bool Show() override;
	bool AddToGraphic(const std::vector<std::shared_ptr<data::Entity> >& objs) override;
	bool UpdateGraphic(const std::vector<std::shared_ptr<data::Entity> >& objs) override;

private:
	// Callback functions
	static void Resize(int width, int height);
	static void Display(void);
	static void MouseButtonFunc(int button, int state, int x, int y);
	static void MouseWheelFunc(int wheel, int direction, int x, int y);
	static void UpdateFunc(int value);
	static void KeyBoardFunc(unsigned char key, int x, int y);
	static void CloseFunc();

	// Initialize and Clear OpenGL
	bool InitializeGL(const ViewerOpts& vOptions);
	bool ClearGL();

	// View events
	void DrawView();
	void ResizeView(int width, int height);

	// Key and Mouse events
	void MouseButtonEvent(int button, int state, int x, int y);
	void MouseWheelEvent(int wheel, int direction, int x, int y);
	void KeyBoardEvent(unsigned char key, int x, int y);

	// Drawing Topo and geom using opengl calls
	bool Draw(const std::shared_ptr<data::Entity>& pObj);
	bool DrawTopo(const std::shared_ptr<data::Topo>& pTopo);
	bool DrawGeom(const std::shared_ptr<data::Geom>& pGeom);

	// Uppdate Listerner
	bool UpdateListerner();

private:

	GLuint m_objList;
	int m_xpos;
	int m_ypos;
	double m_zoom;
	double m_center[3];
	bool m_bPause;
};
#endif // GL_GRAPHIC_H
//------------------------------------------------------------------