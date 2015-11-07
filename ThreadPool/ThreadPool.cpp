
#include <process.h>  
#include "ThreadPool.h"

ThreadPool::ThreadPool(int thread_count) : num_total_thread_(0), num_running_thread_(0)
{
	initialize();

	AdjustSize(thread_count);
}

ThreadPool::~ThreadPool()
{
	finalise();
}

void ThreadPool::initialize()
{
	thread_vector_.clear();
	clear_queue();

	InitializeCriticalSection(&cs_thread_vector_);
	InitializeCriticalSection(&cs_thread_queue_);
	InitializeCriticalSection(&cs_add_total_num_);
	InitializeCriticalSection(&cs_add_running_num_);

	event_end_ = CreateEvent(0, true, false, NULL);
	event_complete_ = CreateEvent(0, false, false, NULL);
	semaphore_call_ = CreateSemaphore(0, 0,  0x7FFFFFFF, NULL);
	semaphore_del_ = CreateSemaphore(0, 0,  0x7FFFFFFF, NULL);
}

void ThreadPool::finalise()
{
	DeleteCriticalSection(&cs_thread_queue_);
	DeleteCriticalSection(&cs_add_total_num_);
	DeleteCriticalSection(&cs_add_running_num_);
	CloseHandle(event_end_);
	CloseHandle(event_complete_);
	CloseHandle(semaphore_call_);
	CloseHandle(semaphore_del_);

	vector<ThreadItem*>::iterator iter;
	for(iter = thread_vector_.begin(); iter != thread_vector_.end(); ++iter)
	{
		if (NULL != *iter)
		{
			ThreadItem* temp = *iter;
			delete temp;
			temp = NULL;
		}
	}
	DeleteCriticalSection(&cs_thread_vector_);
}

void ThreadPool::clear_queue()
{
	while(!job_queue_.empty())
		job_queue_.pop();
}

void ThreadPool::add_total_thread() 
{ 
	EnterCriticalSection(&cs_add_total_num_);
	++num_total_thread_; 
	LeaveCriticalSection(&cs_add_total_num_);
}

void ThreadPool::sub_total_thread() 
{ 
	EnterCriticalSection(&cs_add_total_num_);
	--num_total_thread_; 
	LeaveCriticalSection(&cs_add_total_num_);
}

void ThreadPool::add_running_thread() 
{ 
	EnterCriticalSection(&cs_add_running_num_);
	++num_running_thread_; 
	LeaveCriticalSection(&cs_add_running_num_);
}

void ThreadPool::sub_running_thread()
{
	EnterCriticalSection(&cs_add_running_num_);
	--num_running_thread_; 
	LeaveCriticalSection(&cs_add_running_num_);
}

void ThreadPool::AdjustSize(int num)
{
	if (num <= 0)
		num = 4;
		
	EnterCriticalSection(&cs_thread_vector_);
	for (int i = 0; i < num; ++i)
	{
		ThreadItem* new_thread_item_ptr = new ThreadItem(this);
		thread_vector_.push_back(new_thread_item_ptr);
		new_thread_item_ptr->handle = (HANDLE)_beginthreadex(NULL, 0, JobProc, new_thread_item_ptr, 0, NULL);
	}
	LeaveCriticalSection(&cs_thread_vector_);
}

void ThreadPool::earse_from_vector(ThreadItem* thread_item_ptr)
{
	EnterCriticalSection(&cs_thread_vector_);
	thread_vector_.erase(find(thread_vector_.begin(), thread_vector_.end(), thread_item_ptr));
	LeaveCriticalSection(&cs_thread_vector_);
}

JobItem* ThreadPool::get_job_from_queue(bool &has_job)
{
	JobItem* job_item_ptr = NULL;
	has_job = false;

	EnterCriticalSection(&cs_thread_queue_);
	if (has_job = !job_queue_.empty())
	{
		job_item_ptr = job_queue_.front();
		job_queue_.pop();
	}
	LeaveCriticalSection(&cs_thread_queue_);

	return job_item_ptr;
}

void ThreadPool::Call(void (*pfunc)(void *), void *param)
{
    if (NULL == pfunc)
		return ;

	EnterCriticalSection(&cs_thread_queue_);
	job_queue_.push(new JobItem(pfunc, param));
	LeaveCriticalSection(&cs_thread_queue_);

	ReleaseSemaphore(semaphore_call_, 1, NULL);
}

void ThreadPool::Call(ThreadJob *pjob, void *param)
{
	Call(CallProc, new CallProcParam(pjob, param));
}

void ThreadPool::CallProc(void* param)
{
	CallProcParam *cp = static_cast<CallProcParam*>(param);
	if (NULL == cp)
		return;

	cp->obj_ptr->DoJob(cp->param_ptr);
	delete cp;
	cp = NULL;
}

bool ThreadPool::EndAndWait(unsigned long ul_wait_time)
{
	SetEvent(event_end_);

	return WAIT_OBJECT_0 == WaitForSingleObject(event_complete_, ul_wait_time);
}

unsigned int __stdcall ThreadPool::JobProc(void* param)
{
	ThreadItem* thread_item = static_cast<ThreadItem*>(param);
	if (NULL == thread_item)
		return 0;

	ThreadPool* pool_ptr = thread_item->pool_ptr;
	if (NULL == pool_ptr)
		return 0;

	pool_ptr->add_total_thread();

	HANDLE wait_handle[HANDLE_COUNT];
	wait_handle[0] = pool_ptr->semaphore_call();
	wait_handle[1] = pool_ptr->semaphore_del();
	wait_handle[2] = pool_ptr->event_end();

	JobItem* job_item_ptr = NULL;
	bool has_job = false;

	while(true)
	{
		unsigned long ul = WaitForMultipleObjects(HANDLE_COUNT, wait_handle, false, INFINITE);

		//响应删除线程信号
		if (ul == WAIT_OBJECT_0 + 1)
			break;

		//从队列里取得用户作业
		job_item_ptr = pool_ptr->get_job_from_queue(has_job);

		//受到结束线程信号 确定是否结束线程(结束线程信号 && 是否还有工作)
		if (ul == WAIT_OBJECT_0 + 2 && !has_job)
			break;

		if (has_job && NULL != job_item_ptr)
		{
			pool_ptr->add_running_thread();
			thread_item->ul_last_begin_time = GetTickCount();
			thread_item->ul_count++;
			thread_item->is_running = true;
			job_item_ptr->func(job_item_ptr->func_param);
			delete job_item_ptr;
			job_item_ptr = NULL;
			thread_item->is_running = false;
			pool_ptr->sub_running_thread();
		}
	}

	//删除自身结构
	pool_ptr->earse_from_vector(thread_item);
	delete thread_item;
	thread_item = NULL;

	pool_ptr->sub_total_thread();

	//所有线程结束
	if (0 == pool_ptr->num_total_thread())
		SetEvent(pool_ptr->event_complete());	

	return 1;
}