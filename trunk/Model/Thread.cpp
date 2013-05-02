#include "Thread.h"

Thread::Thread(){
}

int Thread::start(){
	return pthread_create(&(this->thread),NULL,staticRun,(void*)this);
}

void* Thread::staticRun(void* arguments){
	Thread* pThread = (Thread*) arguments;
	pThread->run();
	return NULL;
}

void* Thread::join(){
	void* status;
	pthread_join(this->thread,&status);
	return status;
}

Thread::~Thread(){
}