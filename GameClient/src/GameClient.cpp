/*
 * TCPMSNClient.cpp
 *
 *  Created on: Jun 12, 2017
 *      Author: user
 */

#include "GameClient.h"

namespace npl {

//configure the handler
GameClient::GameClient(AbstractClientHandler* handler) {
	_handler = handler;
	_socket = NULL;
	_connected = false;

}

bool GameClient::connect(string ip) {

	_socket = new TCPSocket(ip, MSNGR_PORT);
	if (_socket->getSocket() < 0)
		return false;

	_connected = true;
	_handler->onRecieveMessage("connected to server");
	this->start();	//start receive loop
	return true;

}

//open session with another peer
bool GameClient::gameRequest(string clientName) {
	if (_connected == false) {
		_handler->onError("offline");
		return false;
	}

	if (!sendCommand(REQUEST, clientName.c_str())) {
		_handler->onError("error sending game request");
		return false;
	}

	return true;
}

void GameClient::run() {

	bool booli = true;
	stringstream str;
	while (booli) {
		int command;
		_socket->read((char*) &command, 4);
		command = ntohl(command);
		string line;
		switch (command) {
		//error
		case ERRORNAME:
			_handler->onError(readServerMessage());
			break;
			//message
		case MESSAGE:
			_handler->onRecieveMessage(readServerMessage());
			break;
			//game invation
		case REQUEST:
			_handler->matchOffer(readServerMessage());

			break;

		case DISCONNECT:
			_connected = false;
			booli = false;
			break;

		case ACCEPT:
			_handler->gameStarting("");
			break;

			//guest
		case CONNECT_TO_PEER:
			sleep(1);
			_handler->gameStarting(readServerMessage());
			break;

		case REJECT:
			_handler->gameRejected(readServerMessage());
			break;
		}
	}

}

string GameClient::readServerMessage() {
	int len;
	if (_socket->read((char*) &len, 4) < 0) {
		_handler->onError("error reading msg size from tcp socket");
		_socket->close();
		return NULL;
	}
	len = ntohl(len);
	char buffer[256];
	memset((void*) buffer, 0, 256);
	if (_socket->read(buffer, len) < 0) {
		_handler->onError("error reading msg size from tcp socket");
		_socket->close();
		return NULL;
	}

	return string(buffer);

}

//send command
bool GameClient::sendCommand(int command, const char* args) {
	command = htonl(command);
	if (_socket->write((char*) &command, 4) < 0) {
		_handler->onError("Error writing command Integer");
		_socket->close();
		return false;
	}

	if (args != NULL) {

		int len = strlen(args);
		int nlen = htonl(len);

		if (_socket->write((char*) &nlen, 4) < 0) {
			_handler->onError(
					"Error writing command argument: error in message length");
			_socket->close();
			return false;
		}

		if (_socket->write(args, len) < 0) {
			_handler->onError(
					"Error writing command argument: error in message length");
			_socket->close();
			return false;
		}
	}
	return true;
}

bool GameClient::disconnect() {

	if (!_connected)
		return false;
	bool b = sendCommand(DISCONNECT, NULL);
	return b;

}
GameClient::~GameClient() {
	if (_socket != NULL)
		_socket->close();

}

bool GameClient::userRegister(const char* details) {

	return sendCommand(REGISTERCOMMAND, details);
}
bool GameClient::userLogin(const char* details) {
	return sendCommand(LOGINCOMMAND, details);
}
bool GameClient::onlineList() {
	return sendCommand(LIST, NULL);
}
bool GameClient::recordList() {
	return sendCommand(RECORDS, NULL);
}
bool GameClient::autoMatch() {
	return sendCommand(AUTOMATCH, NULL);
}
bool GameClient::invite(const char* user) {
	return sendCommand(REQUEST, user);
}
bool GameClient::accept(const char* user) {
	return sendCommand(ACCEPT, user);
}
bool GameClient::reject(const char* user) {
	return sendCommand(REJECT, user);
}

bool GameClient::gameOver(int score) {
	stringstream str;
	str<<score;
	_handler->gameOver(str.str());
return sendCommand(GAMEOVER,str.str().c_str());
}

} /* namespace npl */
