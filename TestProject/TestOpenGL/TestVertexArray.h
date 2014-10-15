#ifndef _TEST_VERTEX_ARRAY_H_
#define _TEST_VERTEX_ARRAY_H_

class TestVertexArray
{
public:
	TestVertexArray();
	~TestVertexArray();
	void start(int argc, char *argv[]);
	void init();
	static void display();
	static void reshape(int width, int height);
private:

};

#endif