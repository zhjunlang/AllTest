
#ifndef THREAD_H_
#define THREAD_H_

#include <Windows.h>
#include <process.h>

class Thread
{
public:
	Thread();
	virtual ~Thread();

public:
	void Initialize();
	void Start();
	virtual void Run() = 0;
	void Stop();
	void Finalise();
	
	bool IsStop();

protected:
	static unsigned int __stdcall ThreadProc(void* param = NULL);

private:
	bool stop_flag_;
	HANDLE thread_;
};


#endif