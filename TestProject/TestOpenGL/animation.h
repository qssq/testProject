#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <iostream>
#include <gl/glut.h>

using namespace std;

class Animation
{
public:
	Animation();
	~Animation();
	void start(int argc, char *argv[]);
	void init();
	
	static void display();
	static void reshape(int width, int height);
	static void mouse(int button, int state, int x, int y);
	static void spinDisplay();
private:

};

#endif