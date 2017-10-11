/*
 * UDPSocket.cpp
 *
 *  Created on: Apr 3, 2017
 *      Author: user
 */

#include "UDPSocket.h"



namespace npl {




UDPSocket::UDPSocket(int port):Socket(SOCK_DGRAM){

Socket::bind(port);
}

int UDPSocket::read(char* buffer,int length){


	unsigned fsize = sizeof(from);
	int n=recvfrom(socket_fd,buffer,length,0,(struct sockaddr *)&from,&fsize);
	if(n<0)
	{
		errorAndClose("UDPSocket::error receiving message");

	return -1;
	}
if(connect(fromAddr(),ntohs(from.sin_port))<0)
	{
	errorAndClose("UDPSocket::error connecting in receive message");

	return -1;
	}

return n;
}



int UDPSocket::write(string msg, string ip, int port){

	if(connect(ip, port)<0)
	{
		errorAndClose("UDPSocket::error connecting on sending message");
		return -1;
	}

	int n=Socket::write(msg.c_str(),msg.length());
	if(n<0)
	{
		errorAndClose("UDPSocket::error sending message");
		return -1;
	}
return n;

}


int UDPSocket::reply(string msg){

	int n=Socket::write(msg.c_str(),msg.length());
	if(n<0)
		{
		errorAndClose("UDPSocket::error replying message");
			return -1;
		}
	return n;
}



} /* namespace networkingLab */
