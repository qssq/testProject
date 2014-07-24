#ifndef _THREAD_HELPER_H_
#define _THREAD_HELPER_H_

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

class ThreadHelper
{
public:
	ThreadHelper();
	~ThreadHelper();
	void ThreadTest();
private:
	void my_thread();
	void my_thread2();
	int mNum;
	mutex mMutex; 
};
#endif