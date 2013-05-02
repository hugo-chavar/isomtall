#include "ConditionVariable.h"

ConditionVariable::ConditionVariable() {
	pthread_cond_init(&(this->conditionVariable),NULL);
}

Mutex& ConditionVariable::getConditionMutex() {
	return this->conditionMutex;
}

pthread_cond_t& ConditionVariable::getConditionVariable() {
	return this->conditionVariable;
}

int ConditionVariable::wait() {
	return pthread_cond_wait(&(this->getConditionVariable()),&(this->getConditionMutex().getMutex()));
}

int ConditionVariable::signal() {
	return pthread_cond_signal(&(this->getConditionVariable()));
}

ConditionVariable::~ConditionVariable() {
	pthread_cond_destroy(&(this->conditionVariable));
}