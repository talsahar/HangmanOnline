/*
 * Dispatcher.h
 *
 *  Created on: Jun 30, 2017
 *      Author: user
 */

#ifndef SRC_DISPATCHER_H_
#define SRC_DISPATCHER_H_
#include "IdentifiedTCP.h"
#include"MThread.h"
#include "MultipleTCPSocketsListener.h"
#include "TCPMessengerProtocol.h"
namespace npl {

class DispatcherHandler {
public:
	//virtual void managePeerSession(TCPSocket* peer1,TCPSocket* peer2)=0;
	virtual char* readSocketArgs(TCPSocket* socket)=0;
	virtual void sendToClient(TCPSocket* socket, string list)=0;
	virtual void errorCommand(TCPSocket* socket, string error)=0;
	virtual void matchRequest(TCPSocket* socket, string name)=0;
	virtual void matchReject(TCPSocket* socket,string name)=0;
	virtual void startMatch(IdentifiedTCP* s1, IdentifiedTCP* s2)=0;
	virtual void onGameOver(IdentifiedTCP* socket)=0;
	virtual void disconnect(TCPSocket* socket)=0;
	virtual void getRecordList(IdentifiedTCP* socket)=0;
	virtual ~DispatcherHandler() {	}
};

class Dispatcher: public MThread {

	DispatcherHandler* handler;
	MultipleTCPSocketsListener listener;
	bool listening;

	IdentifiedTCP* checkForAutoMatcher(IdentifiedTCP* exceptIt);
	IdentifiedTCP* findUser(const char* name);
	string getUserList();

public:
	Dispatcher(DispatcherHandler* handler);
	~Dispatcher();
	void addPeer(IdentifiedTCP* peer);
	void stop();
	void run();
	void analyzeReadySocket(IdentifiedTCP* socket);

};

} /* namespace npl */

#endif /* SRC_DISPATCHER_H_ */
