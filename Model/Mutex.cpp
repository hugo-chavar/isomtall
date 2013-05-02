#include "Mutex.h"

Mutex::Mutex(){
	pthread_mutex_init(&(this->mutex),NULL);
}

pthread_mutex_t& Mutex::getMutex(){
	return this->mutex;
}

int Mutex::lock(){
	return pthread_mutex_lock(&(this->mutex));
}

bool Mutex::tryLock(){
	bool locked = false;

	if (pthread_mutex_trylock(&(this->mutex)) == 0)
		locked = true;

	return locked;
}

int Mutex::unlock(){
	return pthread_mutex_unlock(&(this->mutex));
}

Mutex::~Mutex(){
	pthread_mutex_destroy(&(this->mutex));
}