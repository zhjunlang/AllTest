
#include <iostream>
#include "glog/logging.h" 
#include "ThreadPool.h"

#define TEST_FUNC

void threadfunc(void *param)
{
	cout<<"threadfunc\n";
}

class TestJob : public ThreadJob
{
public:
	TestJob() {}
	~TestJob() {}

public:
	void DoJob(void *p)
	{
		if (NULL != p)
		{
			int *value = static_cast<int*>(p);

			cout<<"--> " << *value << "\n";
		}
	}
};

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(*argv);
	google::SetLogDestination(google::INFO,"C://"); 

	char str[20] = "hello log!";    
    LOG(INFO) << "Found " << google::COUNTER <<endl; 

	ThreadPool *thread_pool_ptr = new ThreadPool(4);
	if (NULL == thread_pool_ptr)
		return 0;

#ifndef TEST_FUNC
	for(int i = 0; i < 10; ++i)
	{
		thread_pool_ptr->Call(threadfunc);
		Sleep(500);
	}
#else
	TestJob *testjob = new TestJob[10];
	if (NULL == testjob)
		return 0;

	for(int i = 0; i < 10; ++i)
	{
		thread_pool_ptr->Call(testjob + i, &i);
		Sleep(500);
	}

	Sleep(10000);
	delete [] testjob;
	testjob = NULL;
#endif

	delete thread_pool_ptr;
	thread_pool_ptr = NULL;

	return 0;
}