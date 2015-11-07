
#ifndef CALL_PROC_PARAM_H_
#define CALL_PROC_PARAM_H_

class ThreadJob;

//用户对象结构
struct CallProcParam
{
	ThreadJob *obj_ptr;	//用户对象
	void* param_ptr;		//用户参数

	CallProcParam(ThreadJob* obj, void* param) : obj_ptr(obj), param_ptr(param) {}
};

#endif