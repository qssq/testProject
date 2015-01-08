#ifndef _TEST_VERTEX_ARRAY_H_
#define _TEST_VERTEX_ARRAY_H_

#include "COpenGLBase.h"

class TestVertexArray : public COpenGLBase
{
public:
	TestVertexArray(int argc, char* argv[]);
	~TestVertexArray();
	static void display();
	static void reshape(int width, int height);
private:

};

#endif