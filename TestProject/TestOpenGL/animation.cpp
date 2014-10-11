#include "animation.h"

static GLfloat spin = 0.0f;

Animation::Animation()
{

}

Animation::~Animation()
{

}

void Animation::init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_FLAT);
	glLoadIdentity();								//原点移到屏幕中心点
	glOrtho(1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f);	//左右下上近远
	
}

