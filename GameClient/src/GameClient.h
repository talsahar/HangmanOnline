/*
 * TCPMSNClient.h
 *
 *  Created on: Jun 12, 2017
 *      Author: user
 */

#ifndef SRC_GAMECLIENT_H_
#define SRC_GAMECLIENT_H_

#include "TCPSocket.h"
#include "MThread.h"
#include "TCPMessengerProtocol.h"
#include "AbstractClientHandler.h"
#include <sstream>
#include <string>

namespace npl {



class GameClient :public MThread{

	TCPSocket* _socket;
	AbstractClientHandler* _handler;




public:
	bool _connected;

	GameClient(AbstractClientHandler* handler);
	virtual ~GameClient();
	bool connect(string ip);//connect to server
	bool userRegister(const char* details);
	bool userLogin(const char* details);
	bool onlineList();
	bool recordList();
	bool autoMatch();
	bool invite(const char* user);
	bool accept(const char* user);
	bool reject(const char* user);
	bool gameOver(int score);
	bool gameRequest(string clientName);


	bool disconnect();

	string readServerMessage();

	bool sendCommand(int command,const char* args);


	void run();



};

} /* namespace npl */

#endif /* SRC_GAMECLIENT_H_ */
