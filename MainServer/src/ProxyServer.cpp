/*
 * ProxyServer.cpp
 *
 *  Created on: Aug 9, 2017
 *      Author: user
 */

#include "ProxyServer.h"

namespace npl {

ProxyServer::ProxyServer(ServerHandler* handler) {
	this->handler=handler;
	this->isRunning=false;
	newSocket=new TCPSocket(MSNGR_PORT);

}

void ProxyServer::run(){
	isRunning=true;


	while(isRunning){
		TCPSocket* listener=newSocket->listenAndAccept();
		if(listener!=NULL)
		handler->handleNewPeer(listener);
	}
}

void ProxyServer::stop(){
	isRunning=false;
	newSocket->close();

}

} /* namespace npl */
