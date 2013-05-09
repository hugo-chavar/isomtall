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

std::map<unsigned int,std::string>& Instruction::getArguments() {
	return this->arguments;
}

std::string Instruction::getArgument(unsigned int key) {
	std::string argument = "";
	std::map<unsigned int,std::string>::iterator it = this->getArguments().find(key);

	if (it != this->getArguments().end())
		argument = it->second;

	return argument;
}

void Instruction::insertArgument(unsigned int key, std::string value) {
	this->getArguments().insert(std::pair<unsigned int,std::string>(key,value));
}

void Instruction::deserialize(std::string serializedInstruction) {
	std::vector<std::string> instructionParams;

	stringUtilities::splitString(serializedInstruction,instructionParams,'|');

	this->setOpCode(stringUtilities::stringToInt(instructionParams[0]));
	for (unsigned int i = 1; i < instructionParams.size(); i = i + 2) {
		this->insertArgument(static_cast<unsigned int>(stringUtilities::stringToInt(instructionParams[i])),instructionParams[i + 1]);
	}
}

std::string Instruction::serialize() {
	std::string serializedInstruction = "";
	this->getOpCode();
	serializedInstruction += stringUtilities::intToString(this->getOpCode());
	for (std::map<unsigned int,std::string>::iterator it = this->getArguments().begin(); it != this->getArguments().end(); ++it) {
		serializedInstruction += "|";
		serializedInstruction += stringUtilities::intToString(static_cast<unsigned int>(it->first));
		serializedInstruction += "|";
		serializedInstruction += it->second;
	}

	return serializedInstruction;
}

Instruction::~Instruction(){
}

