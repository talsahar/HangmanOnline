/*
 * Player.h
 *
 *  Created on: Aug 15, 2017
 *      Author: user
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_
#include "UDPSocket.h"
#include "HangedManStatus.h"
#include "UDPGameProtocol.h"

namespace npl {

class Player {
protected:
	HangedManStatus manPrinter;
	UDPSocket* socket;
	bool playing;
	int score;
	Player(int localPort);

	bool sendCommand(int command, char* args);
	char* readMessage(char* buffer);
	void readWhile();
	void close();
	void onError(string error);
	void printHangedMan(char* status);
	bool retryQ();

	virtual void analyzeMessage(char* msg)=0;
	virtual int send(string msg)=0;
public:
	virtual int startGame()=0;
	virtual ~Player();

};

} /* namespace npl */

#endif /* SRC_PLAYER_H_ */
