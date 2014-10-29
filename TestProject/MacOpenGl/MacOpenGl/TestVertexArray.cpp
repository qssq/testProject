#include "TestVertexArray.h"

#include <GLUT/glut.h>

TestVertexArray::TestVertexArray()
{

}

TestVertexArray::~TestVertexArray()
{

}

void TestVertexArray::start( int argc, char *argv[] )
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("vertex array");
	init();

	glutDisplayFunc(TestVertexArray::display);
	glutReshapeFunc(TestVertexArray::reshape);
	glutMainLoop();
}

void TestVertexArray::init()
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
}

GLint vertices[] = 
{
	25, 25,
	100, 325,
	175, 25,
	175, 325,
	250, 25,
	325, 325
};

GLfloat colors[] =
{
	1, 0.2f, 0.2f,
	0.2f, 0.2f, 1,
	0.8f, 1, 0.2f,
	0.75f, 0.75f, 0.75f,
	0.35f, 0.35f, 0.35f,
	0.5f, 0.5f, 0.5f
};

void TestVertexArray::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(2, GL_INT, 0, vertices);

	glBegin(GL_LINES);
	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(2);
	glArrayElement(3);
	glArrayElement(4);
	glArrayElement(5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(50, 150, 0);
	glVertex3f(150, 150, 0);
	glVertex3f(150, 250, 0);
	glVertex3f(50, 250, 0);
	glEnd();

	glFlush();
}

void TestVertexArray::reshape( int width, int height )
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);
}
