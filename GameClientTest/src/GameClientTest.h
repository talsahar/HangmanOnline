/*
 * GameClientTest.h
 *
 *  Created on: Aug 28, 2017
 *      Author: user
 */

#ifndef SRC_GAMECLIENTTEST_H_
#define SRC_GAMECLIENTTEST_H_
#include "AbstractClientHandler.h"
#include "GameClient.h"
#include<iostream>

using namespace std;
namespace npl {

class GameClientTest :public AbstractClientHandler,MThread{
public:
	bool test();

		void onRecieveMessage(string message);
		void matchOffer(string addr);
		void gameStarting(string message);
		void onError(string error);
		void gameRejected(string message);
		void gameOver(string message);
void run();
};

} /* namespace npl */

#endif /* SRC_GAMECLIENTTEST_H_ */
