#include "InstructionQueue.h"

#include "Logger.h"
#include "SDL.h"
#include "stringUtilities.h"

InstructionQueue::InstructionQueue() {
}

Mutex& InstructionQueue::getMutex() {
	return this->mutex;
}

ConditionVariable& InstructionQueue::getConditionVariable() {
	return this->conditionVariable;
}

std::queue<Instruction>& InstructionQueue::getInstructionQueue() {
	return this->instructionQueue;
}

void InstructionQueue::addInstruction(Instruction& instruction) {
	this->getMutex().lock();
	this->getInstructionQueue().push(instruction);
	this->getMutex().unlock();
	this->getConditionVariable().getConditionMutex().lock();
	this->getConditionVariable().signal();
	this->getConditionVariable().getConditionMutex().unlock();
}

Instruction InstructionQueue::getNextInstruction(bool shouldWait) {
	Instruction aux;

	common::Logger::instance().log("	getNextInstruction - waiting for lock at: " + stringUtilities::unsignedToString(SDL_GetTicks()));
	this->getMutex().lock();
	common::Logger::instance().log("	getNextInstruction - waiting locked at: : " + stringUtilities::unsignedToString(SDL_GetTicks()));
	if (this->getInstructionQueue().empty() && shouldWait) {
		this->getConditionVariable().getConditionMutex().lock();
		this->getMutex().unlock();
		common::Logger::instance().log("	getNextInstruction - waiting for instruction at: " + stringUtilities::unsignedToString(SDL_GetTicks()));
		this->getConditionVariable().wait();
		common::Logger::instance().log("	getNextInstruction - finished waiting for instruction at: " + stringUtilities::unsignedToString(SDL_GetTicks()));
		this->getMutex().lock();
		this->getConditionVariable().getConditionMutex().unlock();
	}

	if (!this->getInstructionQueue().empty()) {
		aux = this->getInstructionQueue().front();
		this->getInstructionQueue().pop();
	}
	this->getMutex().unlock();

	common::Logger::instance().log("	getNextInstruction - returning instruction " + aux.serialize() + " at: " + stringUtilities::unsignedToString(SDL_GetTicks()));
	return aux;
}

void InstructionQueue::lock() {
	this->getMutex().lock();
}

void InstructionQueue::unLock() {
	this->getMutex().unlock();
}

void InstructionQueue::stopWaiting() {
	this->getConditionVariable().getConditionMutex().lock();
	this->getConditionVariable().signal();
	this->getConditionVariable().getConditionMutex().unlock();
}

InstructionQueue::~InstructionQueue() {
}
