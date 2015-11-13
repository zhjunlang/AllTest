
#ifndef TIMER_H_
#define TIMER_H_

#include "Thread.h"

class Timer : public Thread
{
	typedef void(CALLBACK *TimerFunc)(void* param);
	typedef TimerFunc TimerHandler;

public:
	Timer();
	~Timer();

public:
	void RegisterHandler(TimerHandler handler, void* param);
	void Cancel();

	void interval(int interval) { interval_ = interval; }
	int interval() { return interval_; }

public:
	void Run();

private:
	TimerHandler handler_;
	int interval_;
	void* param_;
};

#endif