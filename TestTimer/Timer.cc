
#include "Timer.h"

Timer::Timer() : Thread(), handler_(nullptr), interval_(0), param_(nullptr)
{
}

Timer::~Timer()
{
}

void Timer::RegisterHandler(TimerHandler handler, void* param)
{
	handler_ = handler;
	param_ = param;
}

void Timer::Cancel()
{
	Stop();
}

void Timer::Run()
{
	unsigned long tick_now = ::GetTickCount();
	unsigned long tick_last = tick_now;

	while (!IsStop())
	{
		tick_now = ::GetTickCount();
		if (tick_now - tick_last > interval_)
		{
			if (nullptr != handler_)
			{
				(*handler_)(param_);
			}
			tick_last = ::GetTickCount();
		}

		Sleep(1);
	}
}