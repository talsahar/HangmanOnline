/*
 * ProxyServer.h
 *
 *  Created on: Aug 9, 2017
 *      Author: user
 */

#ifndef SRC_PROXYSERVER_H_
#define SRC_PROXYSERVER_H_
#include "TCPSocket.h"
#include "MThread.h"
#include "TCPMessengerProtocol.h"
namespace npl {


class ServerHandler{
	public:
		virtual void handleNewPeer(TCPSocket* peer)=0;
		virtual ~ServerHandler(){}
	};

class ProxyServer:public MThread{
	TCPSocket* newSocket;
	ServerHandler* handler;
	bool isRunning;
public:
	ProxyServer(ServerHandler* handler);

		void run();
		void stop();
	};

} /* namespace npl */

#endif /* SRC_PROXYSERVER_H_ */
