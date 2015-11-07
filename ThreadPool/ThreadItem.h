
#ifndef THREAD_ITEM_H_
#define THREAD_ITEM_H_

#include <Windows.h>

class ThreadPool;

//�̳߳��е��߳̽ṹ
struct ThreadItem
{
	HANDLE handle;						//�߳̾��
	ThreadPool *pool_ptr;				//�̳߳�ָ��
	unsigned long ul_last_begin_time;	//���һ�����п�ʼʱ��
	unsigned long ul_count;				//���д���
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