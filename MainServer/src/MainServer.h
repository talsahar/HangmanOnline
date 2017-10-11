/*
  * MainServer.h
 *
 *  Created on: Aug 9, 2017
 *      Author: user
 */

#ifndef SRC_MAINSERVER_H_
#define SRC_MAINSERVER_H_
#include "ProxyServer.h"
#include "UserLogin.h"
#include "Dispatcher.h"
#include "RecordList.h"

#include <iostream>
using namespace std;
namespace npl {

class MainServer: public ServerHandler,
		public UserHandler,
		public DispatcherHandler
		{

	ProxyServer* proxy;
	UserLogin* userLogin;
	Dispatcher* dispatcher;
	RecordList* records;

	bool sendMessage(TCPSocket* socket, int command, string args);

public:
	void start();
	void stop();

	char* readSocketArgs(TCPSocket* socket);
	//from ProxyServer
	void handleNewPeer(TCPSocket* peer);

	//from UserLogin
	void loginStatus(TCPSocket* socket, int status);
	void registerStatus(TCPSocket* socket, int status);
	void disconnect(TCPSocket* socket);
	void errorCommand(TCPSocket* socket, string error);

	//from dispatcher
	void sendToClient(TCPSocket* socket, string msg);
	void matchRequest(TCPSocket* socket, string name);
	void startMatch(IdentifiedTCP* s1, IdentifiedTCP* s2);
	void matchReject(TCPSocket* socket,string name);
	void onGameOver(IdentifiedTCP* socket);
	void getRecordList(IdentifiedTCP* socket);
};

} /* namespace npl */

#endif /* SRC_MAINSERVER_H_ */
