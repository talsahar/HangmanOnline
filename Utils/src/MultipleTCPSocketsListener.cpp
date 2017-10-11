#include "MultipleTCPSocketsListener.h"

/*
 * Add the given socket to the socket list to be listen on
 */
void MultipleTCPSocketsListener::addSocket(TCPSocket* socket) {

	list.insert(list.begin(), socket);
}

/*
 * Set the given sockets to the socket list to be listen on
 */
void MultipleTCPSocketsListener::addSockets(vector<TCPSocket*> socketVec) {

	list.insert(list.begin(), socketVec.begin(), socketVec.end());
}

/*
 * This method checks to see if any of the previous given sockets are ready for reading
 * It returns one of the Sockets that are ready.
 */
TCPSocket* MultipleTCPSocketsListener::listenToSocket() {

	vector<TCPSocket*>::iterator iter = list.begin();
	vector<TCPSocket*>::iterator endIter = list.end();

	//create local set for the select function (fd_set)
	fd_set fdset;
	FD_ZERO(&fdset);

	//fill the set with file descriptors from the socket list using (FD_SET macro) ,save highest fd for select
	int highfd = 0;
	for (; iter != endIter; iter++) {
		if (highfd < (*iter)->getSocket())
			highfd = (*iter)->getSocket();
		FD_SET((*iter)->getSocket(), &fdset);
	}

	//perform the select
	int returned;
	if (useTV) {

		returned = select(highfd + 1, &fdset, NULL, NULL, &tv);
	}

	else {

		returned = select(highfd + 1, &fdset, NULL, NULL, NULL);

	}

	//check the returned value from the select to find the socket that is ready
	if (returned) {
		iter = list.begin();
		for (; iter != endIter; iter++) {
			TCPSocket* tmp = *iter;
			//if select return a valid socket return the matching TCPSocket object otherwise return NULL
			int fd = tmp->getSocket();
			if (FD_ISSET(fd, &fdset)) {
				FD_ZERO(&fdset);
				return tmp;
			}
		}
	}
	//	cerr<<"MultipleTCPSocketListener:: ready socket didn't found!"<<endl;
	FD_ZERO(&fdset);
	return NULL;
}

TCPSocket* MultipleTCPSocketsListener::removeFromList(string ip, int port) {

	vector<TCPSocket*>::iterator iter = list.begin();
	vector<TCPSocket*>::iterator endIter = list.end();
	for (; iter != endIter; iter++) {
		if (((*iter)->fromAddr() == ip) && ((*iter)->getPeerPort() == port)) {
			TCPSocket* rSocket = *iter;
			list.erase(iter);
			return rSocket;

		}
	}

	return NULL;

}

void MultipleTCPSocketsListener::setTimer(int sec, int usec) {
	useTV = true;
	tv.tv_sec = 3;
	tv.tv_usec = 0;
}

TCPSocket* MultipleTCPSocketsListener::removeFromList(TCPSocket* socket) {

	vector<TCPSocket*>::iterator iter = list.begin();
	vector<TCPSocket*>::iterator endIter = list.end();
	for (; iter != endIter; iter++) {
		if ((*iter) == socket) {
			TCPSocket* rSocket = *iter;
			list.erase(iter);
			return rSocket;

		}
	}

	return NULL;
}

bool MultipleTCPSocketsListener::isEmpty() {
	if (list.empty())
		return true;
	return false;
}
void MultipleTCPSocketsListener::clear() {

	vector<TCPSocket*>::iterator iter = list.begin();
	vector<TCPSocket*>::iterator endIter = list.end();
	for (; iter != endIter; iter++) {
		(*iter)->close();
	}
	vector<TCPSocket*>().swap(list);
}



vector<TCPSocket*> MultipleTCPSocketsListener::getList() {
return this->list;
}

MultipleTCPSocketsListener::~MultipleTCPSocketsListener() {
clear();
}
