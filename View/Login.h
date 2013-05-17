#ifndef _MODEL_LOGIN_H_
#define _MODEL_LOGIN_H_

#pragma warning(disable: 4512)

#include <list>
#include <string>

#include "LoginUpdater.h"

namespace model {
	class Login {
		private:
			LoginUpdater loginUpdater;

			Mutex messagesListMutex;

			std::list<std::string> messagesList;

		public:
			Login();

			//TEMPORARY. THIS SHOULD BE PRIVATE.
			LoginUpdater& getLoginUpdater();

			bool isLoggedIn();

			Mutex& getMessagesListMutex();

			std::list<std::string>& getMessagesList();

			void initialize();

			void update();

			void cleanUp();

			~Login();
	};
} // namespace model

#endif // _MODEL_LOGIN_H_