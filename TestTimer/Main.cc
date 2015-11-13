
#include <iostream>
#include "glog/logging.h" 
#include "Timer.h"

void CALLBACK TimerProc(void* param)
{
	int *i = static_cast<int*>(param);
	if (nullptr == i)
		return ;

	std::cout<<"TimerProc: "<<*i<<"\n";
}

int main()
{
	google::InitGoogleLogging("TestTimer");
	google::SetLogDestination(google::INFO,"./../Debug/TestTimer_");

	LOG(INFO) << "TestTimer Start";

	Timer timer;
	
	int i = 10;
	void* param = &i;
	timer.RegisterHandler(TimerProc, param);
	timer.interval(1000);
	timer.Start();

	Sleep(1000);

	for (int i = 0; i < 20; ++i)
	{
		std::cout << "hello\n";
        Sleep(1000);
	}
	timer.Cancel();

	return 0;
}