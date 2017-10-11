/*
 * Socket.h
 *
 *  Created on: May 30, 2017
 *      Author: user
 */

#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#include "FileInterface.h"


using namespace std;

namespace npl {

class Socket {
protected:
	int socket_fd;
	struct sockaddr_in from;
	struct sockaddr_in local;


public:

virtual ~Socket(){}
	Socket(int type);
	Socket(int connected_sock,struct sockaddr_in localAddr,struct sockaddr_in serverAddr);
	bool bind(int port);
	bool connect(string ip,int port);
	virtual int read(char* buffer,int length);//recv
	virtual int write(const char* msg,int length);//send
	void errorAndClose(string error);


	void close();
	string fromAddr();
	int getSocket();

	int getLocalPort();
	int getPeerPort();

	sockaddr_in getLocalAddr();
	sockaddr_in getPeerAddr();

};

} /* namespace socketName */

#endif /* SRC_SOCKET_H_ */
