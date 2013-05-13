#ifndef _INSTRUCTIONQUEUE_H_
#define _INSTRUCTIONQUEUE_H_

#include <queue>

#include "Mutex.h"
#include "Instruction.h"
#include "ConditionVariable.h"

class InstructionQueue {
private:
	Mutex mutex;

	ConditionVariable conditionVariable;

	std::queue<Instruction> instructionQueue;

	Mutex& getMutex();

	ConditionVariable& getConditionVariable();

//	std::queue<Instruction>& getInstructionQueue();

public:
	InstructionQueue();

	void addInstruction(Instruction& instruction);

	Instruction getNextInstruction(bool shouldWait);


	//TODO: FIND A BETTER WAY.
	void lock();

	std::queue<Instruction>& getInstructionQueue();

	void unLock();

	
	void stopWaiting();

	~InstructionQueue();
};

#endif // _INSTRUCTIONQUEUE_H_