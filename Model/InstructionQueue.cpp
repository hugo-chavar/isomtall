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

	common::Logger::instance().log("getNextInstruction - 1 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));
	this->getMutex().lock();
	common::Logger::instance().log("getNextInstruction - 2 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));
	if (this->getInstructionQueue().empty() && shouldWait) {
		common::Logger::instance().log("getNextInstruction - 3 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));
		this->getConditionVariable().getConditionMutex().lock();
		common::Logger::instance().log("getNextInstruction - 4 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));
		this->getMutex().unlock();
		common::Logger::instance().log("getNextInstruction - 5 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));
		this->getConditionVariable().wait();
		common::Logger::instance().log("getNextInstruction - 6 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));
		this->getMutex().lock();
		common::Logger::instance().log("getNextInstruction - 7 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));
		this->getConditionVariable().getConditionMutex().unlock();
		common::Logger::instance().log("getNextInstruction - 8 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));
	}

	if (!this->getInstructionQueue().empty()) {
		common::Logger::instance().log("getNextInstruction - 9 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));
		aux = this->getInstructionQueue().front();
		common::Logger::instance().log("getNextInstruction - 10 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));
		this->getInstructionQueue().pop();
		common::Logger::instance().log("getNextInstruction - 11 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));
	}
	this->getMutex().unlock();
	common::Logger::instance().log("getNextInstruction - 12 AT: " + stringUtilities::unsignedToString(SDL_GetTicks()));

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
