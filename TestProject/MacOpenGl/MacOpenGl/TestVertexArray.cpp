#include "TestVertexArray.h"

#include <GLUT/glut.h>

TestVertexArray::TestVertexArray()
{
    setDisplayFunc(TestVertexArray::display);
    setReshapeFunc(TestVertexArray::reshape);
}

TestVertexArray::~TestVertexArray()
{

}

//步骤2
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
    1, 1, 1,
    1, 0, 1,
    0, 1, 1,
    0, 1, 1,
    1, 1, 1,
    1, 0, 1,
    0, 1, 1,
    0, 1, 1
};

GLfloat cubes[] =
{
    0, 0, -100,
    200, 0, -100,
    200, 200, -100,
    0, 200, -100,
    0, 0, 100,
    200, 0, 100,
    200, 200, 100,
    0, 200, 100
};

//正方体
static GLubyte frontIndices[] = {4, 5, 6, 7};

static GLubyte rightIndices[] = {1, 2, 6, 5};

static GLubyte bottomIndices[] = {0, 1, 5, 4};

static GLubyte backIndices[] = {0, 3, 2, 1};

static GLubyte leftIndices[] = {0, 4, 7, 3};

static GLubyte topIndices[] = {2, 3, 7, 6};

void TestVertexArray::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
    
    //步骤1
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, cubes);

    //步骤3 正方体
    
    //方法1
//    glBegin(GL_QUADS);
//    glArrayElement(0);
//    glArrayElement(1);
//    glArrayElement(2);
//    glArrayElement(3);
//    glEnd();
    
    //方法2
    glDrawArrays(GL_QUADS, 0, 4);
//    glMultiDrawElements()
    
    //方法3
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frontIndices);
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, rightIndices);
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bottomIndices);
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, backIndices);
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, leftIndices);
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, topIndices);
    
    //方法4
//    GLsizei couts[] = {4, 4, 4, 4, 4, 4};
//    GLvoid *indeces[] = {frontIndices, rightIndices, bottomIndices, backIndices, leftIndices, topIndices};
//    glMultiDrawElements(GL_QUADS, couts, GL_UNSIGNED_BYTE, indeces, 6);
    
	glFlush();
}

void TestVertexArray::reshape( int width, int height )
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width/2, width/2, -height/2, height/2, -100, 100);
}
