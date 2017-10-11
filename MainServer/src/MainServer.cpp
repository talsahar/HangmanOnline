/*
 * MainServer.cpp
 *
 *  Created on: Aug 9, 2017
 *      Author: user
 */

#include "MainServer.h"
namespace npl {

void MainServer::start() {

	records = new RecordList();

	proxy = new ProxyServer(this);
	proxy->start();

	userLogin = new UserLogin(this, records);
	dispatcher = new Dispatcher(this);

}

void MainServer::handleNewPeer(TCPSocket* peer) {
	sendToClient(peer,
			"please identify yourself\nlogin [login user:pass]\nregister [register user:pass]\n");
	userLogin->addUser(peer);
}

//STATUS:-1 not exists,-2 incorrect password,-3 fileNotOpen,-4 illegal args, 0+ score (succeed)
void MainServer::loginStatus(TCPSocket* socket, int status) {

	switch (status) {
	case -1:
		errorCommand(socket, "user not exists\n");
		break;
	case -2:
		errorCommand(socket, "incorrect password\n");
		break;
	case -3:
		errorCommand(socket, "couldn't login bug on server's database\n");
		break; //file not found
	case -4:
		errorCommand(socket, "illegal login arguments please try again\n");
		break;
	default: // return to dispatcher
		sendToClient(socket,
				"you have been logged on.\nenter 'list' to see another online users\n");
		dispatcher->addPeer((IdentifiedTCP*) socket);
	}
}
// STATUS::-1 illegal args, -2 exists user, 0 register succeed
void MainServer::registerStatus(TCPSocket* socket, int status) {

	switch (status) {
	case -1:
		errorCommand(socket, "illegal register arguments please try again\n");
		break;
	case -2:
		errorCommand(socket,
				"the username is not exists on the list please try again or register\n");
		break;
	case 0:
		sendToClient(socket,
				"register succeed\nplease login [login user:pass]\n");
	}

}

bool MainServer::sendMessage(TCPSocket* socket, int command, string args) {

	const char* charArgs = args.c_str();
	command = htonl(command);

	//writing command
	if (socket->write((char*) &command, 4) < 4) {
		cerr << "error writing command integer" << endl;
		return false;
	}

	//sending args
	if (strcmp(charArgs, "") != 0) {

		int len = args.length();
		int nlen = htonl(len);
		//length
		if (socket->write((char*) &nlen, 4) < 4) {
			cerr << "error writing command argument: error in message length"
					<< endl;
			return false;
		}
		//data
		if (socket->write(charArgs, len) < 0) {
			cerr << "error writing command argument: error sending message"
					<< endl;
			return false;

		}

	}
	return true;
}

void MainServer::disconnect(TCPSocket* socket) {
	sendMessage(socket, DISCONNECT, "");
	sleep(2);
	socket->close();
}
void MainServer::errorCommand(TCPSocket* socket, string error) {
	sendMessage(socket, ERRORNAME, error);
}

void MainServer::sendToClient(TCPSocket* socket, string msg) {

	sendMessage(socket, MESSAGE, msg);
}

void MainServer::matchRequest(TCPSocket* socket, string name) {
	sendMessage(socket, REQUEST, name);
}

void MainServer::matchReject(TCPSocket* socket, string name) {
	sendMessage(socket, REJECT,name);


}

void MainServer::getRecordList(IdentifiedTCP* socket) {
	sendMessage(socket, MESSAGE, records->getFullRecordList());
}

void MainServer::startMatch(IdentifiedTCP* s1, IdentifiedTCP* s2) {
	s1->setBusyStatus(true);
	s2->setBusyStatus(true);
	s1->setAutoMatchStatus(false);
	s2->setAutoMatchStatus(false);

	sendMessage(s2, ACCEPT, "");
	sendMessage(s1, CONNECT_TO_PEER, s2->fromAddr());

}

void MainServer::onGameOver(IdentifiedTCP* socket) {

	char buffer[30];
	strcpy(buffer, socket->getScore().c_str());
	buffer[socket->getScore().length()] = '\0';
	records->add(socket->getName(), atoi(buffer));
	userLogin->updateScore(socket->getName(), buffer);
	dispatcher->addPeer(socket);
}

void MainServer::stop() {
	proxy->stop();
	dispatcher->stop();
	userLogin->stop();

}

char* MainServer::readSocketArgs(TCPSocket* socket){
			int len; //reading data length
			socket->read((char*) &len, 4);
			len = ntohl(len);
			char* buffer=new char[1000];
			memset((void*) buffer, 0, 1000);
			int r = socket->read(buffer, len); //reading data
			buffer[r] = 0;
return buffer;

}


}
