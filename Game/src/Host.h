/*
 * Host.h
 *
 *  Created on: Aug 15, 2017
 *      Author: user
 */

#ifndef SRC_HOST_H_
#define SRC_HOST_H_

#include "Player.h"

namespace npl {

class Host: public Player {

char topic[15];
char word[15];
char secret[15];
int guestLife;
public:
	Host();
	~Host();
		int startGame();
		void analyzeMessage(char* msg);

		int send(string msg);
		char* getTopicAndWord();
		char* buildMessage();
		bool checkGuessValid(char* guess);
		bool checkGuestWin();
};

} /* namespace npl */

#endif /* SRC_HOST_H_ */
