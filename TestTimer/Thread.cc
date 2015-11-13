
#include "Thread.h"

Thread::Thread() : stop_flag_(false), thread_(INVALID_HANDLE_VALUE)
{
	Initialize();
}

Thread::~Thread()
{
	Stop();
	Finalise();
}
void Thread::Initialize()
{
}

void Thread::Start()
{
	unsigned *p = nullptr;
	thread_ = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, this, 0, p);
}

void Thread::Stop()
{
	stop_flag_ = true;

	if (thread_ != INVALID_HANDLE_VALUE)
	{
		if (WAIT_ABANDONED != WaitForSingleObject(thread_, INFINITE))
		{
			CloseHandle(thread_);
			thread_ = INVALID_HANDLE_VALUE;
		}
	}
}

bool Thread::IsStop()
{
	return stop_flag_;
}

void Thread::Finalise()
{
}

unsigned int __stdcall Thread::ThreadProc(void* param)
{
	Thread *thread = static_cast<Thread*>(param);
	if (nullptr != thread)
		return 0;

	thread->Run();

	CloseHandle(thread->thread_);
	thread->thread_ = INVALID_HANDLE_VALUE;

	return 0;
}