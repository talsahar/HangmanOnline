/*
 * UserLogin.h
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#ifndef SRC_USERLOGIN_H_
#define SRC_USERLOGIN_H_
#include "Authentication.h"
#include "TCPMessengerProtocol.h"
#include "MultipleTCPSocketsListener.h"
#include "IdentifiedTCP.h"
#include "MThread.h"
#include "RecordList.h"
namespace npl {

class UserHandler{
public:
	virtual char* readSocketArgs(TCPSocket* socket)=0;
	virtual void loginStatus(TCPSocket* socket,int status)=0;
	virtual void registerStatus(TCPSocket* socket,int status)=0;
	virtual void disconnect(TCPSocket* socket)=0;
	virtual void errorCommand(TCPSocket* socket,string error)=0;

	virtual ~UserHandler(){}
};

class UserLogin :public MThread{
	Authentication* verify;
	UserHandler* handler;

	MultipleTCPSocketsListener listener;
	bool listening;
public:
	UserLogin(UserHandler* handler,RecordList* recordList);

	void addUser(TCPSocket* socket);
	void run();
	void stop();
	void readySocket(TCPSocket* readySock);
	void updateScore(char* name,char* score);
};

} /* namespace npl */

#endif /* SRC_USERLOGIN_H_ */
