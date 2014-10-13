#include "animation.h"

#include <complex>

static GLfloat spin = 0.0f;

Animation::Animation()
{

}

Animation::~Animation()
{

}



void Animation::start( int argc, char *argv[] )
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("doubel openGL");  
	init();

	glutDisplayFunc(Animation::display);
	glutReshapeFunc(Animation::reshape);
	glutMouseFunc(Animation::mouse);

	glutMainLoop();
}

void Animation::init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_FLAT);
	//glLoadIdentity();								//原点移到屏幕中心点
	//glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);	//左右下上近远
	
}

void Animation::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin, 0, 0, 1);
	glColor3f(1, 0, 1);
	//glutSolidSphere(0.5f, 10, 10);

	//glRectf(-100, -100, 100, 100);

	const float PI = 3.1415926f;
	int circlePoints = 100;
	float angle(0);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < circlePoints; i++)
	{
		angle = 2 * PI * i / circlePoints;
		glVertex2f(cos(angle) * 100, sin(angle) * 100);
	}
	glEnd();

	glPopMatrix();
	glutSwapBuffers();

	glFlush();
}

void Animation::reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();								//原点移到屏幕中心点
	glOrtho(-width/2, width/2, -height/2, height/2, -1.0f, 1.0f);	//左右下上近远
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Animation::mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			glutIdleFunc(spinDisplay);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			glutIdleFunc(NULL);
		}
		break;
	default:
		break;
	}
}

void Animation::spinDisplay()
{
	spin += spin + 2;
	if (spin > 360)
	{
		spin = 0;
	}
	glutPostRedisplay();
}

