

#ifndef MULTIPLETCPSOCKETSLISTENER_H_
#define MULTIPLETCPSOCKETSLISTENER_H_

#include <vector>
#include "TCPSocket.h"


using namespace npl;


class MultipleTCPSocketsListener{

	vector<TCPSocket*> list;
	bool useTV;

		struct timeval tv;



public:
	/*
	 * Add the given socket to the socket list to be listen on
	 */
	void addSocket(TCPSocket* socket);

	/*
	 * Set the given sockets to the socket list to be listen on
	 */
	void addSockets(vector<TCPSocket*> socketVec);

	/*
	 * This method checks to see if any of the previous given sockets are ready for reading
	 * It returns one of the Sockets that are ready.
	 */
	TCPSocket* listenToSocket();


	TCPSocket* removeFromList(string ip,int port);
	TCPSocket* removeFromList(TCPSocket* socket);

	bool isEmpty();
	void setTimer(int sec,int usec);
	void clear();

	~MultipleTCPSocketsListener();

	vector<TCPSocket*> getList();
};


#endif /* MULTIPLETCPSOCKETSLISTENER_H_ */
