
#ifndef JOB_ITEM_H_
#define JOB_ITEM_H_

//�û������ṹ
struct JobItem 
{
	void (*func)(void *);
	void *func_param;

	JobItem(void (*p)(void  *) = 0, void *param = 0) : func(p), func_param(param) {};
};

#endif