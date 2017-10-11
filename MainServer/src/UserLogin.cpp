/*
 * UserLogin.cpp
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#include "UserLogin.h"

namespace npl {

UserLogin::UserLogin(UserHandler* handler, RecordList* recordList) {
	this->handler = handler;

	verify = new Authentication(VERIFYFILENAME);
	verify->loadRecords(recordList);
	listening = false;

	listener.setTimer(3, 0);
}

void UserLogin::addUser(TCPSocket* socket) {
	listener.addSocket(socket);
	if (listening == false) {
		listening = true;
		start();
	}
}

void UserLogin::run() {

	while (!listener.isEmpty()) {
		TCPSocket* ready = listener.listenToSocket();
		if (ready != NULL) {
			readySocket(ready);
		}
	}
	listening = false;
}

void UserLogin::readySocket(TCPSocket* readySock) {

	//reading command
	int command;
	readySock->read((char*) &command, 4);
	command = ntohl(command);
	if (command == REGISTERCOMMAND || command == LOGINCOMMAND) {

char* buffer=handler->readSocketArgs(readySock);
		char* user;
		char* pass;
		user = strtok(buffer, ":");
		pass = strtok(NULL, ":");
		if (command == REGISTERCOMMAND) {
			handler->registerStatus(readySock,
					verify->userRegister(user, pass));
		} else if (command == LOGINCOMMAND) {
			int status = verify->userLogin(user, pass);
			//if status>=0 its a score and we create the IdentifiedTCP socket (player)
			if (status >= 0) {
				IdentifiedTCP* verifiedSocket = new IdentifiedTCP(readySock,
						user, status);
				listener.removeFromList(readySock);
				readySock = verifiedSocket;
			}
			handler->loginStatus(readySock, status);
		}

	} else if (command == DISCONNECT)
		handler->disconnect(listener.removeFromList(readySock));

	else
		handler->errorCommand(readySock, "unknown login command");

}

void UserLogin::stop() {
	listener.clear();
}
void UserLogin::updateScore(char* name, char* score) {
	verify->updateScore(name, score);
}

} /* namespace npl */
