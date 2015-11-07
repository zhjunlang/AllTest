
#ifndef THREAD_ITEM_H_
#define THREAD_ITEM_H_

#include <Windows.h>

class ThreadPool;

//线程池中的线程结构
struct ThreadItem
{
	HANDLE handle;						//线程句柄
	ThreadPool *pool_ptr;				//线程池指针
	unsigned long ul_last_begin_time;	//最后一次运行开始时间
	unsigned long ul_count;				//运行次数
	bool is_running;

	ThreadItem(ThreadPool *pool) : pool_ptr(pool), handle(NULL), ul_last_begin_time(0), ul_count(0), is_running(false)
	{
	}

	~ThreadItem()
	{
		if (NULL != handle) { CloseHandle(handle); handle = NULL; }
	}
};


#endif