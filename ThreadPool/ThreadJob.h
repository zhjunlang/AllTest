
#ifndef THREAD_JOB_H_
#define THREAD_JOB_H_

class ThreadJob
{
public:
	virtual void DoJob(void* pParam) = 0;
};

#endif