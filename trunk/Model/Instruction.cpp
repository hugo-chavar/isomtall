#include "Instruction.h"

#include <string>
#include <utility>

#include "StringUtilities.h"
#include "Constants.h"

Instruction::Instruction() {
	this->opCode = OPCODE_NO_OPCODE;
}

void Instruction::clear() {
	this->setOpCode(OPCODE_NO_OPCODE);
	this->getArguments().clear();
}

void Instruction::setOpCode(unsigned int opCode) {
	this->opCode = opCode;
}

unsigned int Instruction::getOpCode() const {
	return this->opCode;
}

std::map<std::string,std::string>& Instruction::getArguments() {
	return this->arguments;
}

std::string Instruction::getArgument(std::string name) {
	std::string argument = "";
	std::map<std::string,std::string>::iterator it = this->getArguments().find(name);

	if (it != this->getArguments().end())
		argument = it->second;

	return argument;
}

void Instruction::insertArgument(std::string name, std::string value) {
	this->getArguments().insert(std::pair<std::string,std::string>(name,value));
}

void Instruction::deserialize(std::string serializedInstruction) {
	std::vector<std::string> instructionParams;

	StringUtilities::splitString(serializedInstruction,instructionParams,'|');

	this->setOpCode(StringUtilities::stringToInt(instructionParams[0]));
	for (unsigned int i = 1; i < instructionParams.size(); i = i + 2) {
		this->insertArgument(instructionParams[i],instructionParams[i + 1]);
	}
}

std::string Instruction::serialize() {
	std::string serializedInstruction = "";
	this->getOpCode();
	serializedInstruction += StringUtilities::intToString(this->getOpCode());
	for (std::map<std::string,std::string>::iterator it = this->getArguments().begin(); it != this->getArguments().end(); ++it) {
		serializedInstruction += "|";
		serializedInstruction += it->first;
		serializedInstruction += "|";
		serializedInstruction += it->second;
	}

	return serializedInstruction;
}

Instruction::~Instruction(){
}

