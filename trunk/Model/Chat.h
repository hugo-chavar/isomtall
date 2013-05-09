#ifndef _MODEL_CHAT_H_
#define _MODEL_CHAT_H_

#include <list>
#include <string>

#include "ChatUpdater.h"

namespace model {
	class Chat {
		private:
//			bool loggedIn;

			ChatUpdater chatUpdater;

			std::string inputBuffer;

			Mutex messagesListMutex;

			std::list<std::string> messagesList;

//			Socket* socket;

//			Sender* sender;

//			Receiver* receiver;

			std::string to;

//			void setLoggedIn(bool loggedIn);

//			Socket* getSocket();

//			void setSocket(Socket* socket);

//			Sender* getSender();

//			void setSender(Sender* sender);

//			Receiver* getReceiver();

//			void setReceiver(Receiver* receiver);

			std::string getTo();

		public:
			Chat();

			//TEMPORARY. THIS SHOULD BE PRIVATE.
			ChatUpdater& getChatUpdater();

			bool isConnected();

			std::string getInputBuffer();

			void setInputBuffer(std::string inputBuffer);

			Mutex& getMessagesListMutex();

			std::list<std::string>& getMessagesList();

			void setTo(std::string to);

			void sendMessage();

			void initialize();

			void update();

			void cleanUp();

			~Chat();
	};
} // namespace model

#endif // _MODEL_CHAT_H_