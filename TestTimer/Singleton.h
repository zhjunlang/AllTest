
#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <assert.h>

template<typename T>
class Singleton
{
protected:
	static T* singleton_;

public:
	Singleton()
	{
		assert(!singleton_);
		singleton_ = static_cast<T*>(this);
	}

	~Singleton()
	{
		assert(!singleton_);
		singleton_ = nullptr;
	}

	static T& Singleton()
	{
		assert(singleton_);
		return (*singleton_);
	}

	static T* SingletonPtr()
	{
		assert(singleton_);
		return singleton_;
	}
};

#define SINGLETON_INIT( TYPE )								   \
	template<> TYPE * Singleton<TYPE>::singleton_ = nullptr    \

#endif