/*
 * UDPSocket.h
 *
 *  Created on: Apr 3, 2017
 *      Author: user
 */

#ifndef SRC_UDPSOCKET_H_
#define SRC_UDPSOCKET_H_

#include"Socket.h"


namespace npl {



class UDPSocket:public Socket {

public:

	UDPSocket(int port);//init and bind
	int read(char* buffer,int length);	//reading
	int reply(string msg);	//reply
	int write(string msg, string ip, int port);//writing for client
};

}

#endif
