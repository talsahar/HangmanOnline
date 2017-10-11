/*
 * Guest.h
 *
 *  Created on: Aug 15, 2017
 *      Author: user
 */

#ifndef SRC_GUEST_H_
#define SRC_GUEST_H_

#include "Player.h"

namespace npl {

class Guest: public Player {
	string peerIP;
	int peerPort;

public:
	Guest(string peerIP);
	~Guest();
	int startGame();

	int send(string msg);
	void analyzeMessage(char* msg);
	char* getValidGuess();

	void printTopic(char* str);
	bool onGameOver(bool won,string message);


};

} /* namespace npl */

#endif /* SRC_GUEST_H_ */
