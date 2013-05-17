#ifndef _THREAD_H_
#define _THREAD_H_

#include "pthread.h"

class Thread{
private:
	pthread_t thread;

	bool stopping;

	static void* staticRun(void* arguments);

protected:
	Thread();

	bool isStopping();

	void setStopping(bool stopping);

	int start();

	void* join();

	virtual void* run() = 0;

	virtual ~Thread();
};

#endif // _THREAD_H_
