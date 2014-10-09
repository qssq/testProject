#include <iostream>
#include <gl/glut.h>

using namespace std;

void renderScene(void)  
{  
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	glLoadIdentity();  

	glColor3f(1.0f, 0.0f, 0.0f);

	glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

	glBegin(GL_POLYGON);  

	glVertex3f(0.25f, 0.25f, 0.0f);  

	glVertex3f(0.5f, 0.25f, 0.0f);  

	glVertex3f(0.5f, 0.5f, 0.0f);  

	glVertex3f(0.25f, 0.5f, 0.0f);  

	glEnd();  

	glFlush();

	glutSwapBuffers();  
}  

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(33,TimerFunction, 1);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, (char**) argv);  

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  

	glutInitWindowPosition(100, 100);  

	glutInitWindowSize(640, 480);  

	glutCreateWindow("Hello OpenGL");  

	glutDisplayFunc(renderScene);  

	//glutTimerFunc(33, TimerFunction, 1);

	glutMainLoop();//enters the GLUT event processing loop.  
	
	return 0;
}