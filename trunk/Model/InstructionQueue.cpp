#include "InstructionQueue.h"

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

	this->getMutex().lock();
	if (this->getInstructionQueue().empty() && shouldWait) {
		this->getConditionVariable().getConditionMutex().lock();
		this->getMutex().unlock();
		this->getConditionVariable().wait();
		this->getMutex().lock();
		this->getConditionVariable().getConditionMutex().unlock();
	}

	if (!this->getInstructionQueue().empty()) {
		aux = this->getInstructionQueue().front();
		this->getInstructionQueue().pop();
	}
	this->getMutex().unlock();

	return aux;
}

void InstructionQueue::stopWaiting() {
	this->getConditionVariable().getConditionMutex().lock();
	this->getConditionVariable().signal();
	this->getConditionVariable().getConditionMutex().unlock();
}

InstructionQueue::~InstructionQueue() {
}
