#include "ThreadHelper.h"


ThreadHelper::ThreadHelper() : mNum(0)
{

}

ThreadHelper::~ThreadHelper()
{

}

void ThreadHelper::ThreadTest()
{
	thread t(bind(&ThreadHelper::my_thread, this));
	t.detach();
	thread t2(bind(&ThreadHelper::my_thread2, this));
	t2.detach();
	cout<<"hello end"<<endl;
}

void ThreadHelper::my_thread()
{
	mMutex.lock();  
	for (int i = 0; i < 100; i++)
	{
		cout<<"hello "<<++mNum<<endl;
	}
	mMutex.unlock();  
}

void ThreadHelper::my_thread2()
{
	lock_guard<mutex> lg(mMutex);
	this_thread::sleep_for(chrono::milliseconds(3000));
	for (int i = 0; i < 100; i++)
	{
		cout<<"hello "<<++mNum<<endl;
	}
}
