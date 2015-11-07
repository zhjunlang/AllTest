
#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <queue>
#include <vector>
#include "ThreadJob.h"
#include "JobItem.h"
#include "ThreadItem.h"
#include "CallProcParam.h"

using namespace::std;

#define HANDLE_COUNT 3

class ThreadPool
{
public:
	ThreadPool(int thread_count = 4);
	~ThreadPool();

	void initialize();
	void finalise();

	int num_total_thread() { return num_total_thread_; }
	void add_total_thread();
	void sub_total_thread();
	int num_running_thread() { return num_running_thread_; }
	void add_running_thread();
	void sub_running_thread();
	bool is_running() { return num_running_thread_ > 0; }
	void clear_queue();

	HANDLE event_end() { return event_end_; }
	HANDLE event_complete() { return event_complete_; }
	HANDLE semaphore_call() { return semaphore_call_; }
	HANDLE semaphore_del() { return semaphore_del_; }

	void AdjustSize(int num);

	void earse_from_vector(ThreadItem *thread_item);
	JobItem* get_job_from_queue(bool &has_job);

public:
	//调用线程池
	void Call(void (*pfunc)(void *), void *param = NULL);	

	//调用线程池
	void Call(ThreadJob *pjob, void *param = NULL);	

	//结束线程池, 并同步等待
	bool EndAndWait(unsigned long ul_wait_time = INFINITE);

	//结束线程池
	inline void End() { SetEvent(event_end_); }

protected:
	//工作线程
	static unsigned int __stdcall JobProc(void* param = NULL);

	//调用用户对象虚函数
	static void CallProc(void* param);

public:
	CRITICAL_SECTION cs_thread_vector_;		//工作队列临界
	CRITICAL_SECTION cs_thread_queue_;		//线程数据临界
	CRITICAL_SECTION cs_add_total_num_;
	CRITICAL_SECTION cs_add_running_num_;

private:
	int num_total_thread_;					//线程数量
	int num_running_thread_;				//运行的线程数量

	queue<JobItem*> job_queue_;				//工作队列
	vector<ThreadItem*> thread_vector_;		//线程数据

	HANDLE event_end_;						//结束通知
	HANDLE event_complete_;					//完成事件
	HANDLE semaphore_call_;					//工作信号
	HANDLE semaphore_del_;					//删除信号
};


#endif