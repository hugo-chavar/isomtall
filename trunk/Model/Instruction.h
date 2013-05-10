#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#ifndef MESSAGE_ENVELOPE_BEGIN_TAG
#define MESSAGE_ENVELOPE_BEGIN_TAG "<message>"
#endif//MESSAGE_ENVELOPE_BEGIN_TAG

#ifndef MESSAGE_ENVELOPE_END_TAG
#define MESSAGE_ENVELOPE_END_TAG "</message>"
#endif//MESSAGE_ENVELOPE_END_TAG

#ifndef opCode_t
#define opCode_t
enum opCode_t {
	OPCODE_NO_OPCODE,
	OPCODE_INVALID,
	OPCODE_CONNECTION_ERROR,
	OPCODE_SERVER_BUSY,
	OPCODE_LOGIN_REQUEST,
	OPCODE_CONNECT_TO_CHAT,
	OPCODE_CONNECT_TO_SIMULATION,
	OPCODE_UPDATE_REQUEST,
	OPCODE_UPDATE_FILE,
	OPCODE_UPDATE_COMPLETE,
	OPCODE_LOGOUT_REQUEST,
	OPCODE_CHAT_LOGOUT_REQUEST,
	OPCODE_LOGIN_OK,
	OPCODE_USERID_NOT_AVAILABLE,
	OPCODE_CHAT_CONNECTION_ESTABLISHED,
	OPCODE_DISCONNECT,
	OPCODE_CHAT_MESSAGE_IN,
	OPCODE_CHAT_MESSAGE_OUT
};
#endif

#ifndef instructionArgumentKey_t
#define instructionArgumentKey_t
enum instructionArgumentKey_t {
	INSTRUCTION_ARGUMENT_KEY_USER_ID,
	INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID,
	INSTRUCTION_ARGUMENT_KEY_GREETING,
	INSTRUCTION_ARGUMENT_KEY_ERROR,
	INSTRUCTION_ARGUMENT_KEY_FILE,
	INSTRUCTION_ARGUMENT_KEY_MESSAGE,
	INSTRUCTION_ARGUMENT_KEY_FROM,
	INSTRUCTION_ARGUMENT_KEY_TO
};
#endif

#include <map>

#include "Serializable.h"
#include "Constants.h"

class Instruction : public Serializable {
private:
	unsigned int opCode;

	std::map<unsigned int,std::string> arguments;

	std::map<unsigned int,std::string>& getArguments();

public:
	Instruction();

	void clear();

	unsigned int getOpCode() const;

	void setOpCode(unsigned int opCode);

	void insertArgument(unsigned int key,std::string value);

	std::string getArgument(unsigned int key);

	void deserialize(std::string serializedInstruction);

	std::string serialize();

	~Instruction();
};

#endif // _INSTRUCTION_H_