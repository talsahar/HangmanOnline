/*
 * TCPSocket.h
 *
 *  Created on: Apr 28, 2017
 *      Author: user
 */

#ifndef SRC_TCPSOCKET_H_
#define SRC_TCPSOCKET_H_

#include "Socket.h"

namespace npl {

class TCPSocket: public Socket {
public:
	TCPSocket(int connected_sock, struct sockaddr_in localAddr,
			struct sockaddr_in serverAddr); //listen & accept return constractor.
	TCPSocket(int port); //server constractor
	TCPSocket(string peerIp, int port); //client constractor
	TCPSocket* listenAndAccept(); //listen and accept

};

} /* namespace tcpSock */

#endif /* SRC_TCPSOCKET_H_ */
