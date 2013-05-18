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
	OPCODE_DISCONNECT_FROM_CHAT,
	OPCODE_CONNECT_TO_SIMULATION,
	OPCODE_DISCONNECT_FROM_SIMULATION,
	OPCODE_ACTIVATE,
	OPCODE_SIMULATION_SYNCHRONIZE,
	OPCODE_UPDATE_REQUEST,
	OPCODE_UPDATE_FILE_START,
	OPCODE_UPDATE_FILE,
	OPCODE_UPDATE_RECV,
	OPCODE_UPDATE_DIRECTORY,
	OPCODE_UPDATE_FILE_COMPLETE,
	OPCODE_UPDATE_COMPLETE,
	OPCODE_LOGOUT_REQUEST,
	OPCODE_LOGIN_OK,
	OPCODE_USERID_NOT_AVAILABLE,
	OPCODE_CHAT_CONNECTION_ESTABLISHED,
	OPCODE_SIMULATION_CONNECTION_ESTABLISHED,
	OPCODE_SIMULATION_UPDATE,
	OPCODE_CLIENT_COMMAND,
	OPCODE_DISCONNECT,
	OPCODE_CHAT_MESSAGE_IN,
	OPCODE_CHAT_MESSAGE_OUT,
	OPCODE_INIT_SYNCHRONIZE,
	OPCODE_INVALID_CHARACTER
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
	INSTRUCTION_ARGUMENT_KEY_TO,
	INSTRUCTION_ARGUMENT_KEY_SERIALIZED_FILE,
	INSTRUCTION_ARGUMENT_KEY_SERIALIZED_PATH,
	INSTRUCTION_ARGUMENT_KEY_SERIALIZED_DIR,
	INSTRUCTION_ARGUMENT_KEY_CONNECTED_AT,
	INSTRUCTION_ARGUMENT_KEY_COMMAND_DESTINATION,
	INSTRUCTION_ARGUMENT_KEY_CURRENT_POSITION,
	INSTRUCTION_ARGUMENT_KEY_COMMAND_STATE,
	INSTRUCTION_ARGUMENT_KEY_SIMULATION_UPDATE,
	INSTRUCTION_ARGUMENT_KEY_DUMMY,
	INSTRUCTION_ARGUMENT_KEY_VISION,
	INSTRUCTION_ARGUMENT_KEY_CHARACTER,
	INSTRUCTION_ARGUMENT_KEY_CHARACTER_INIT
};
#endif

#include <map>

#include "Serializable.h"

class Instruction : public Serializable {
private:
	unsigned int opCode;

	unsigned int broadcastId;

	std::map<unsigned int,std::string> arguments;

	std::map<unsigned int,std::string>& getArguments();

public:
	Instruction();

	void clear();

	unsigned int getOpCode() const;

	void setOpCode(unsigned int opCode);

	unsigned int getBroadcastId();

    void setBroadcastId(unsigned int broadcastId);

	void insertArgument(unsigned int key,std::string value);

	std::string getArgument(unsigned int key);

	void deserialize(std::string serializedInstruction);

	std::string serialize();

	~Instruction();
};

#endif // _INSTRUCTION_H_