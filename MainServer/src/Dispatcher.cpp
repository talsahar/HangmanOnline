/*
 * Dispatcher.cpp
 *
 *  Created on: Jun 30, 2017
 *      Author: user
 */

#include "Dispatcher.h"

namespace npl {

Dispatcher::Dispatcher(DispatcherHandler* handler) {
	this->handler = handler;
	listening = false;
	listener.setTimer(3, 0);
}

Dispatcher::~Dispatcher() {
	listener.~MultipleTCPSocketsListener();
}

void Dispatcher::addPeer(IdentifiedTCP* peer) {

	listener.addSocket(peer);
	if (listening == false)
		start();

}

void Dispatcher::run() {
	listening = true;

	while (!listener.isEmpty()) {
		IdentifiedTCP* readySocket = (IdentifiedTCP*) listener.listenToSocket();
		if (readySocket != NULL)
			analyzeReadySocket(readySocket);

	}
	listening = false;

}

void Dispatcher::analyzeReadySocket(IdentifiedTCP* socket) {

	//reading command
	int command;
	int tmpInt;
	socket->read((char*) &command, 4);
	command = ntohl(command);
	IdentifiedTCP* tmpSocket;
	char* str;
	switch (command) {
	case LIST:
		handler->sendToClient(socket, getUserList());
		break;
	case DISCONNECT:
		listener.removeFromList(socket);
		handler->disconnect(socket);
		break;
	case AUTOMATCH:
		tmpSocket = checkForAutoMatcher(socket);
		if (tmpSocket == NULL) {
			socket->setAutoMatchStatus(true);
			handler->sendToClient(socket, "waiting for another auto-matcher");
		} else {
			handler->startMatch(socket, tmpSocket);
		}
		break;

	case RECORDS:
		handler->getRecordList(socket);
		break;

	case REQUEST:
		str = handler->readSocketArgs(socket);
		if (str == socket->getName())
			handler->errorCommand(socket, "cannot invite yourself");
		else {
			tmpSocket = findUser(str);
			if (tmpSocket != NULL) {
				if (tmpSocket->getAutoMatchStatus() == true) { //the other is on automatch mode
					handler->startMatch(tmpSocket, socket);
				} else
					//send request
					handler->matchRequest(tmpSocket, socket->getName());
			} else
				handler->errorCommand(socket, "unknown or busy user");

		}

		break;
	case ACCEPT:

		str = handler->readSocketArgs(socket);
		tmpSocket = findUser(str);
		if (tmpSocket != NULL)
			handler->startMatch(tmpSocket, socket);
		else
			handler->matchReject(socket, str);
		break;
	case REJECT:
		str = handler->readSocketArgs(socket);
		tmpSocket = findUser(str);
		if (tmpSocket != NULL)
			handler->matchReject(tmpSocket, socket->getName());
		break;
	case GAMEOVER:
		str = handler->readSocketArgs(socket);
		tmpInt = atoi(str);
		socket->updateScore(tmpInt);
		socket->setBusyStatus(false);
		handler->onGameOver(socket);
		break;


	}

}

void Dispatcher::stop() {
	listener.clear();
}

IdentifiedTCP* Dispatcher::checkForAutoMatcher(IdentifiedTCP* exceptIt) {
	std::vector<TCPSocket*> socketVector = listener.getList();
		  for (std::vector<TCPSocket*>::iterator iter = socketVector.begin() ; iter != socketVector.end(); ++iter){

		if (dynamic_cast<IdentifiedTCP*>(*iter)->getAutoMatchStatus() == true
				&& dynamic_cast<IdentifiedTCP*>(*iter)->getBusyStatus() == false
				&& (*iter != exceptIt))
			return dynamic_cast<IdentifiedTCP*>(*iter);
	}
	return NULL;
}

string Dispatcher::getUserList() {
	std::vector<TCPSocket*> socketVector = listener.getList();
	string messageList = "user list\n---------\n";
		  for (std::vector<TCPSocket*>::iterator iter = socketVector.begin() ; iter != socketVector.end(); ++iter){

		messageList += string(dynamic_cast<IdentifiedTCP*>(*iter)->getName()) +=
				" | score: ";
		messageList += dynamic_cast<IdentifiedTCP*>(*iter)->getScore() += "\n";
	}

	return messageList;
}

IdentifiedTCP* Dispatcher::findUser(const char* name) {
	std::vector<TCPSocket*> socketVector = listener.getList();
	  for (std::vector<TCPSocket*>::iterator iter = socketVector.begin() ; iter != socketVector.end(); ++iter){
		if (strcmp(dynamic_cast<IdentifiedTCP*>(*iter)->getName(), name) == 0
				&& dynamic_cast<IdentifiedTCP*>(*iter)->getBusyStatus()
						== false)
			return dynamic_cast<IdentifiedTCP*>(*iter);
	}
	return NULL;
}


} /* namespace npl */
