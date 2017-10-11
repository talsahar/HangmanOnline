/*
 * Socket.cpp
 *
 *  Created on: May 30, 2017
 *      Author: user
 */

#include "Socket.h"

namespace npl {

//socket constractor
Socket::Socket(int type) {
	socket_fd = socket(AF_INET, type, 0);

}

Socket::Socket(int connected_sock, struct sockaddr_in localAddr,
		struct sockaddr_in serverAddr) {
	this->socket_fd = connected_sock;
	this->local = localAddr;
	this->from = serverAddr;
}

bool Socket::bind(int port) {
	bzero((char*) &local, sizeof(local));
	local.sin_family = (short) AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	if (::bind(socket_fd, (struct sockaddr*) &local, sizeof(local)) < 0) {
		errorAndClose("Error naming local channel");
		return false;
	}
	return true;
}

bool Socket::connect(string ip, int port) {
	bzero((char*) &from, sizeof(from));
	from.sin_family = AF_INET;
	from.sin_port = htons(port);
	from.sin_addr.s_addr = inet_addr(ip.data());

	if (::connect(socket_fd, (struct sockaddr *) &from, sizeof(from)) < 0) {
		errorAndClose("Error Connecting to peer");
		return false;
	}
	return true;
}

void Socket::errorAndClose(string error) {
	cerr << error << endl;
	close();
}

int Socket::read(char* buffer, int length) {
	return ::read(socket_fd, buffer, length);
}

int Socket::write(const char* msg, int length) {
	return ::write(socket_fd, msg, length);
}

void Socket::close() {
	shutdown(socket_fd, SHUT_RDWR);
	::close(socket_fd);
}

int Socket::getSocket() {
	return socket_fd;
}

string Socket::fromAddr() {
	return inet_ntoa(from.sin_addr);
}

int Socket::getLocalPort() {
	return ntohs(local.sin_port);
}


int Socket::getPeerPort() {
	return ntohs(from.sin_port);
}

sockaddr_in Socket::getLocalAddr(){
	return local;
}
	sockaddr_in Socket::getPeerAddr(){
return from;
	}

} /* namespace socketName */
