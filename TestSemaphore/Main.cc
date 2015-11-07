
#include <iostream>
#include <windows.h>
#include <process.h>

long g_num;
unsigned int _stdcall threadfunc(void *param);
const int Thread_Num = 10;
CRITICAL_SECTION g_threadcode;
HANDLE handle_semaphore;

using std::cout;

int main()
{
	g_num = 0;

	HANDLE handle[Thread_Num];

	InitializeCriticalSection(&g_threadcode);
	handle_semaphore = CreateSemaphore(NULL, 0, 1, NULL);
	for(int i = 0; i < Thread_Num; ++i)
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, threadfunc, &i, 0, NULL);
		WaitForSingleObject(handle_semaphore, INFINITE);
	}
	WaitForMultipleObjects(Thread_Num, handle, true, INFINITE);
	DeleteCriticalSection(&g_threadcode);
	CloseHandle(handle_semaphore);

	return 0;
}

unsigned int _stdcall threadfunc(void *param)
{
	int *value = static_cast<int *>(param);
	EnterCriticalSection(&g_threadcode);
	Sleep(0);
	cout<<"线程编号为:"<<*value<<" 全局资源值为:"<<g_num++<<"\n";
	LeaveCriticalSection(&g_threadcode);

	ReleaseSemaphore(handle_semaphore, 1, NULL);

	return 0;
}