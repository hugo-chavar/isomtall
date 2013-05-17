#include "Thread.h"

// ----------------------------------- CONSTRUCTOR ---------------------------------------

Thread::Thread(){
	this->stopping = false;
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

void* Thread::staticRun(void* arguments){
	Thread* pThread = (Thread*) arguments;
	pThread->run();
	return NULL;
}

// ----------------------------------- PROTECTED METHODS ---------------------------------

bool Thread::isStopping() {
	return this->stopping;
}

void Thread::setStopping(bool stopping) {
	this->stopping = stopping;
}

int Thread::start(){
	return pthread_create(&(this->thread),NULL,staticRun,(void*)this);
}

void* Thread::join(){
	void* status;
	pthread_join(this->thread,&status);
	return status;
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

Thread::~Thread(){
}