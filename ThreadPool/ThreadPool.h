
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
	//�����̳߳�
	void Call(void (*pfunc)(void *), void *param = NULL);	

	//�����̳߳�
	void Call(ThreadJob *pjob, void *param = NULL);	

	//�����̳߳�, ��ͬ���ȴ�
	bool EndAndWait(unsigned long ul_wait_time = INFINITE);

	//�����̳߳�
	inline void End() { SetEvent(event_end_); }

protected:
	//�����߳�
	static unsigned int __stdcall JobProc(void* param = NULL);

	//�����û������麯��
	static void CallProc(void* param);

public:
	CRITICAL_SECTION cs_thread_vector_;		//���������ٽ�
	CRITICAL_SECTION cs_thread_queue_;		//�߳������ٽ�
	CRITICAL_SECTION cs_add_total_num_;
	CRITICAL_SECTION cs_add_running_num_;

private:
	int num_total_thread_;					//�߳�����
	int num_running_thread_;				//���е��߳�����

	queue<JobItem*> job_queue_;				//��������
	vector<ThreadItem*> thread_vector_;		//�߳�����

	HANDLE event_end_;						//����֪ͨ
	HANDLE event_complete_;					//����¼�
	HANDLE semaphore_call_;					//�����ź�
	HANDLE semaphore_del_;					//ɾ���ź�
};


#endif