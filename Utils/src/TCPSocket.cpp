/*
 * TCPSocket.cpp
 *
 *  Created on: Apr 28, 2017
 *      Author: user
 */

#include "TCPSocket.h"

namespace npl {

TCPSocket::TCPSocket(int connected_sock, struct sockaddr_in localAddr,
		struct sockaddr_in serverAddr) :
		Socket(connected_sock, localAddr, serverAddr) {
}

TCPSocket::TCPSocket(int port) :
		Socket(SOCK_STREAM) {

	int optval = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, 4); //prevent file descriptor error
	Socket::bind(port);

}

TCPSocket::TCPSocket(string peerIp, int port) :
		Socket(SOCK_STREAM) {

	if(!connect(peerIp, port))
		this->socket_fd=-1;

}

TCPSocket* TCPSocket::listenAndAccept() {

	printf("Server is alive and waiting for socket connection from client.\n");
	int rc = listen(socket_fd, 1);
	if (rc < 0) {
		errorAndClose("TCPSocket::Error listening");
		return NULL;
	}

	unsigned int len = sizeof(from);
	int connect_sock = accept(socket_fd, (struct sockaddr *) &from, &len);
	if (connect_sock < 0) {
		errorAndClose("Error accepting connection.");

		return NULL;
	} else
		return new TCPSocket(connect_sock, local, from);
}

} /* namespace tcpSock */
