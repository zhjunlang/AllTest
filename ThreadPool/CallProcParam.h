
#ifndef CALL_PROC_PARAM_H_
#define CALL_PROC_PARAM_H_

class ThreadJob;

//�û�����ṹ
struct CallProcParam
{
	ThreadJob *obj_ptr;	//�û�����
	void* param_ptr;		//�û�����

	CallProcParam(ThreadJob* obj, void* param) : obj_ptr(obj), param_ptr(param) {}
};

#endif