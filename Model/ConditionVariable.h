#ifndef _CONDITIONVARIABLE_H_
#define _CONDITIONVARIABLE_H_

#include "pthread.h"
#include "Mutex.h"

class ConditionVariable{
private:
	Mutex conditionMutex;

	pthread_cond_t conditionVariable;

	unsigned int broadcastId;

	void setBroadcastId(unsigned int broadcastId);

	pthread_cond_t& getConditionVariable();

public:
	ConditionVariable();
	//TODO: WHY PUBLIC???
	Mutex& getConditionMutex();

	int wait();

	unsigned int getBroadcastId();

	unsigned int getNextBroadcastId();

	int broadcast();

	int signal();

	~ConditionVariable();
};

#endif // _CONDITIONVARIABLE_H_
