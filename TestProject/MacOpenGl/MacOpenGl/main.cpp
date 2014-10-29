#include <iostream>
#include <GLUT/glut.h>

#include "TestAnimation.h"
#include "TestLines.h"
#include "TestVertexArray.h"

using namespace std;


void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//initialize viewing values
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();								//原点移到屏幕中心点
	glOrtho(1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f);	//左右下上近远
}

void display()  
{  
	glClear(GL_COLOR_BUFFER_BIT);  
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_POLYGON);  
	glVertex3f(0.25f, 0.25f, 0.0f);  
	glVertex3f(0.75f, 0.25f, 0.0f); 
	glVertex3f(0.75f, 0.75f, 0.0f);  
	glVertex3f(0.25f, 0.75f, 0.0f);  
	glEnd();

	glFlush();
	glutSwapBuffers();
}  

void reshape( int width, int height)
{

}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		glClear(GL_COLOR_BUFFER_BIT); 

		glutWireCube(0.5f);

		glFlush();
	}
	else if (key == 'b')
	{
		glClear(GL_COLOR_BUFFER_BIT); 

		glutSolidCube(0.5f);

		glFlush();
	}
	else if (key == 'c')
	{
		glClear(GL_COLOR_BUFFER_BIT); 

		glutWireSphere(0.5f, 100, 100);

		glFlush();
	}
	else if (key == 'd')
	{
		glClear(GL_COLOR_BUFFER_BIT); 

		glutSolidSphere(0.5f, 100, 100);

		glFlush();
	}
}

void mouse(int button, int statte, int x, int y)
{

}

void motion(int x, int y)
{

}

void idle()
{

}

void haha()
{
    for (int i = 0; i <1000; ++i)
    {
        string *newString = new string("1234");
        cout<<*newString<<endl;
    }
}

int main(int argc, char *argv[])
{
	//glutInit(&argc, argv);  
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
	//glutInitWindowSize(480, 480);  
	//glutInitWindowPosition(100, 100);  
	//glutCreateWindow("Hello OpenGL");  
	//init();

	//glutDisplayFunc(display);  
	//glutReshapeFunc(reshape);
	//glutKeyboardFunc(keyboard);
	//glutMouseFunc(mouse);
	//glutMotionFunc(motion);
	//glutIdleFunc(idle);

	//glutMainLoop();
	//
    TestAnimation ta;
    ta.start(argc, argv);
    
	return 0;
}