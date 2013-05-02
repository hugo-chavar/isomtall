#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <map>

#include "Serializable.h"
#include "Constants.h"

class Instruction : public Serializable {
private:
	unsigned int opCode;

	std::map<std::string,std::string> arguments;

	std::map<std::string,std::string>& getArguments();

public:
	Instruction();

	void clear();

	void setOpCode(unsigned int opCode);

	unsigned int getOpCode() const;

	void insertArgument(std::string name,std::string value);

	std::string getArgument(std::string name);

	void deserialize(std::string serializedInstruction);

	std::string serialize();

	~Instruction();
};

#endif // _INSTRUCTION_H_