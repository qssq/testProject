#ifndef _TEST_LINES_H_
#define _TEST_LINES_H_

class TestLines 
{
public:
	TestLines();
	~TestLines();
	void start(int argc, char *argv[]);
	void init();
	static void display();
	static void reshape(int width, int height);

private:
};
#endif