/*
 * ClientCLI.h
 *
 *  Created on: Aug 17, 2017
 *      Author: user
 */

#ifndef CLIENTCLI_H_
#define CLIENTCLI_H_
#include "GameClient.h"
#include "HangedManStatus.h"
#include"string.h"
#include "Guard.h"
#include"Host.h"
#include"Guest.h"
namespace npl {

class ClientCLI:public AbstractClientHandler {

	HangedManStatus manPrinter;
	GameClient* client;
	//offer
	bool offer; //when its on client can use accept command (prevents conflicts)
	string offerUname;

	//game
		bool gameTryLock;
		pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
		Guard* gameGuard;

public:
	void start();
	void serverLoop();

	void printCommandList();
	void printInstructions();
	////
	void onRecieveMessage(string message);
	void matchOffer(string addr);
	void onLogin();

	void onError(string error);
	//from client

	void gameRejected(string message);
	void gameStarting(string message);
	void gameOver(string message);
};

} /* namespace npl */

#endif /* CLIENTCLI_H_ */
