#include "TestLines.h"
#include <gl/glut.h>

#define drawOneLine(x1, y1, x2, y2) glBegin(GL_LINES);\
									glVertex2f(x1, y1);\
									glVertex2f(x2, y2);\
									glEnd();

TestLines::TestLines()
{

}

TestLines::~TestLines()
{

}

void TestLines::start( int argc, char *argv[] )
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("lines");
	init();

	glutDisplayFunc(TestLines::display);
	glutReshapeFunc(TestLines::reshape);
	glutMainLoop();
}

void TestLines::init()
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
}

void TestLines::display()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x0101);
	drawOneLine(50, 125, 150, 125);
	glLineStipple(1, 0x00ff);
	drawOneLine(150, 125, 250, 125);
	glLineStipple(1, 0x1c47);
	drawOneLine(350, 125, 350, 125);

	glLineWidth(5);
	glLineStipple(1, 0x0101);
	drawOneLine(50, 100, 150, 100);
	glLineStipple(1, 0x00ff);
	drawOneLine(150, 100, 250, 100);
	glLineStipple(1, 0x1c47);
	drawOneLine(350, 100, 350, 100);
	glLineWidth(1);

	glLineStipple(1, 0x1c47);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 7; i++)
	{
		glVertex2f(50 + ((GLfloat)i * 50), 75);
	}
	glEnd();
	
	for (int i = 0; i < 6; i++)
	{
		drawOneLine(50 + ((GLfloat)i * 50), 50,
					50 + ((GLfloat)(i + 1) * 50), 50);
	}

	glLineStipple(5, 0x1c47);
	drawOneLine(50, 25, 350, 25);

	glDisable(GL_LINE_STIPPLE);

	glBegin(GL_POLYGON);
	glVertex3f(50, 150, 0);
	glVertex3f(150, 150, 0);
	glVertex3f(150, 250, 0);
	glVertex3f(50, 250, 0);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glEdgeFlag(GL_TRUE);
	glVertex3f(250, 150, 0);
	glEdgeFlag(GL_FALSE);
	glVertex3f(350, 150, 0);
	glEdgeFlag(GL_TRUE);
	glVertex3f(350, 250, 0);
	glEdgeFlag(GL_TRUE);
	glVertex3f(250, 250, 0);
	glEnd();

	glFlush();
}

void TestLines::reshape( int width, int height )
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);
}

