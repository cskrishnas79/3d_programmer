//------------------------------------------------------------------
//
// Graphic using freeglut for display
//
//------------------------------------------------------------------
#include "viewer\graphic\glgraphic.h"
#include "utils\defines.h"

GLGraphic* g_pGraphic = nullptr;

// Start of call back function implementation
void GLGraphic::Resize(int width, int height)
{
	if (g_pGraphic != nullptr)
		g_pGraphic->ResizeView(width, height);
}

void GLGraphic::Display(void)
{
	if (g_pGraphic != nullptr)
		g_pGraphic->DrawView();
}

void GLGraphic::MouseButtonFunc(int button, int state, int x, int y)
{
	if (g_pGraphic != nullptr)
		g_pGraphic->MouseButtonEvent(button, state, x, y);

	glutPostRedisplay();
}

void GLGraphic::MouseWheelFunc(int wheel, int direction, int x, int y)
{
	if (g_pGraphic != nullptr)
		g_pGraphic->MouseWheelEvent(wheel, direction, x, y);

	glutPostRedisplay();
}

void GLGraphic::UpdateFunc(int value)
{
	if (g_pGraphic != nullptr)
	{
		if (g_pGraphic->UpdateListerner() == false)
			return;
	}

	glutPostRedisplay();
	glutTimerFunc(REFRESH_TIME, UpdateFunc, 0);
}
// End of call back function implementation

GLGraphic::GLGraphic(Viewer* pViewer) : m_xpos(0), m_ypos(0), m_zoom(150.0f), IGraphic(pViewer)
{
	m_center[0] = m_center[1] = m_center[2] = 0.0f;
}

GLGraphic::~GLGraphic()
{
	ClearGL();
	g_pGraphic = nullptr;
	m_pViewer = nullptr;
}

bool GLGraphic::InitializeGL(const ViewerOpts& vOptions)
{
	m_objList = glGenLists(1);
	if (m_objList == 0)
		return false;

	glClearColor(vOptions.m_backColor[0], vOptions.m_backColor[1], vOptions.m_backColor[2], vOptions.m_backColor[3]);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	g_pGraphic = this;
	return true;
}

bool GLGraphic::ClearGL()
{
	if (m_objList)
	{
		glDeleteLists(m_objList, 1);
		m_objList = 0;
	}
	return true;
}

bool GLGraphic::UpdateListerner()
{
	if (m_pViewer != nullptr)
		return m_pViewer->UpdateLogic();

	return false;
}

void GLGraphic::ResizeView(int width, int height)
{
	float aspectRatio = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, aspectRatio, 1.0, 500.0);
}

void GLGraphic::DrawView()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(-m_center[0], -m_center[1], -m_zoom);
	// call the list compiled
	glCallList(m_objList);

	glutSwapBuffers();
}

void GLGraphic::MouseButtonEvent(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		int diffX = x - m_xpos;
		int diffY = y - m_ypos;
		m_center[0] -= diffX*PAN_FACTOR;
		m_center[1] += diffY*PAN_FACTOR;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		m_xpos = x;
		m_ypos = y;
	}
}

void GLGraphic::MouseWheelEvent(int wheel, int direction, int x, int y)
{
	if (wheel == 0)
	{
		if (direction > 0)
			m_zoom += ZOOM_FACTOR;
		else
			m_zoom -= ZOOM_FACTOR;
	}
}

bool GLGraphic::DrawTopo(const std::shared_ptr<data::Topo>& pTopo)
{
	bool bRes = false;
	if (pTopo->GetType() == data::TopoType::TOPO_ASSEMBLY)
	{
		std::shared_ptr<data::Assembly> pAssem = std::dynamic_pointer_cast<data::Assembly>(pTopo);
		for (auto inst : pAssem->m_components)
		{
			std::shared_ptr<data::Topo> pTopo = std::dynamic_pointer_cast<data::Topo>(inst);
			bRes = DrawTopo(pTopo);
		}
	}
	else if (pTopo->GetType() == data::TopoType::TOPO_PART)
	{
		std::shared_ptr<data::Part> pPart = std::dynamic_pointer_cast<data::Part>(pTopo);

		glColor3d(pPart->m_display.m_color[0], pPart->m_display.m_color[1], pPart->m_display.m_color[2]);
		glLineWidth(pPart->m_display.m_lineWidth);

		glPolygonMode(GL_FRONT, GL_FILL);
		if (pPart->m_display.m_mode == data::DisplayType::DISPLY_LINE)
			glPolygonMode(GL_FRONT, GL_LINE);
		else if (pPart->m_display.m_mode == data::DisplayType::DISPLY_POINT)
			glPolygonMode(GL_FRONT, GL_POINT);

		const double* val = pPart->m_transform.get();
		glPushMatrix();
		glMultMatrixd(val);

		bRes = DrawGeom(pPart->m_geom);

		glPopMatrix();
	}
	return bRes;
}

bool GLGraphic::DrawGeom(const std::shared_ptr<data::Geom>& pGeom)
{
	bool bRes = false;
	if (pGeom->GetType() == data::GeomType::GEOM_POINT)
	{
		GLObject glObj(GL_POINT);
		bRes = glObj.Point(pGeom);
	}
	else if (pGeom->GetType() == data::GeomType::GEOM_LINE)
	{
		GLObject glObj(GL_LINES);
		bRes = glObj.Line(pGeom);
	}
	else if (pGeom->GetType() == data::GeomType::GEOM_CIRCLE)
	{
		GLObject glObj(GL_POLYGON);
		bRes = glObj.Circle(pGeom);
	}
	else if (pGeom->GetType() == data::GeomType::GEOM_RECTANGLE)
	{
		GLObject glObj(GL_QUADS);
		bRes = glObj.Rectangle(pGeom);
	}
	else if (pGeom->GetType() == data::GeomType::GEOM_POLYGON)
	{
		GLObject glObj(GL_POLYGON);
		bRes = glObj.Polygon(pGeom);
	}

	return bRes;
}

bool GLGraphic::Draw(const std::shared_ptr<data::Entity>& pObj)
{
	bool bRes = false;
	if (pObj->GetEntityType() == data::EntityType::ENT_TOPO)
	{
		std::shared_ptr<data::Topo> pTopo = std::dynamic_pointer_cast<data::Topo>(pObj);
		bRes = DrawTopo(pTopo);
	}
	else if (pObj->GetEntityType() == data::EntityType::ENT_GEOM)
	{
		std::shared_ptr<data::Geom> pGeom = std::dynamic_pointer_cast<data::Geom>(pObj);
		bRes = DrawGeom(pGeom);
	}
	return bRes;
}

// Start Interface methods implementation
bool GLGraphic::Initialize(const ViewerOpts& vOptions)
{
	int argc = 0;
	glutInit(&argc, nullptr);
	glutInitWindowSize(vOptions.m_window_width, vOptions.m_window_height);
	glutInitWindowPosition(vOptions.m_intial_pos[0], vOptions.m_intial_pos[1]);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow(vOptions.m_viewName.c_str());

	// Registering callback functions
	glutReshapeFunc(Resize);
	glutDisplayFunc(Display);
	glutMouseFunc(MouseButtonFunc);
	glutMouseWheelFunc(MouseWheelFunc);
	glutTimerFunc(500, UpdateFunc, 0);
	glutIdleFunc(nullptr);

	// Set action on window close for main loop return to the calling function
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Initializing OpenGL
	bool bRes = InitializeGL(vOptions);
	return bRes;
}

bool GLGraphic::Show()
{
	glutMainLoop();
	// Clear OpenGL
	return ClearGL();
}

bool GLGraphic::AddToGraphic(const std::vector<std::shared_ptr<data::Entity> >& objs)
{
	int len = (int)objs.size();
	if (len == 0)
		return false;

	double min[3] = { 0.0,0.0,0.0 }, max[3] = { 0.0,0.0,0.0 };
	glNewList(m_objList, GL_COMPILE);
	{
		for (int i = 0; i < len; ++i)
		{
			const std::shared_ptr<data::Entity>& obj = objs[i];
			if (i == 0)
			{
				obj->GetBoundingBox(min, max);
			}
			else
			{
				double minP[3] = { 0.0,0.0,0.0 }, maxP[3] = { 0.0,0.0,0.0 };
				obj->GetBoundingBox(minP, maxP);
				min[0] = MIN(min[0], minP[0]);
				min[1] = MIN(min[1], minP[1]);
				min[2] = MIN(min[2], minP[2]);

				max[0] = MAX(max[0], maxP[0]);
				max[1] = MAX(max[1], maxP[1]);
				max[2] = MAX(max[2], maxP[2]);
			}

			Draw(obj);
		}
	}
	glEndList();

	m_center[0] = (max[0] + min[0]) / 2;
	m_center[1] = (max[1] + min[1]) / 2;
	m_center[2] = (max[2] + min[2]) / 2;
	return true;
}

bool GLGraphic::UpdateGraphic(const std::vector<std::shared_ptr<data::Entity> >& objs)
{
	int len = (int)objs.size();
	if (len == 0)
		return false;

	glNewList(m_objList, GL_COMPILE);
	{
		for (auto obj : objs)
			Draw(obj);
	}
	glEndList();
	return true;
}
// End Interface methods implementation