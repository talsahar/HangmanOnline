/*
 * ClientCLI.cpp
 *
 *  Created on: Aug 17, 2017
 *      Author: user
 */

#include "ClientCLI.h"

namespace npl {

void ClientCLI::start() {
client=new GameClient(this);

	manPrinter.welcome();
	cout << "enter 'help' for list of commands" << endl;
	serverLoop();

}

void ClientCLI::serverLoop() {
	string input, param;
	offer = false;
	gameTryLock = false;

	while (true) {
		if (gameTryLock == true) {

			gameGuard=new Guard(&mutex);
			Guard* tmp=new Guard(&mutex);//stuck and reject/gameOver release it. [to ignore the next cin]
			delete tmp;

		}

		cin >> input;

		if (offer == true) {
			if (input == "yes") {
				client->accept(offerUname.c_str());
				gameTryLock=true;

			}

			else
				client->reject(offerUname.c_str());
			offer = false;
		}

		else if (input == "help")
			printCommandList();

		else if (input == "ins")
			printInstructions();

		else if (input == "connect"&&!client->_connected) {
			cin >> input;
			client->connect(input);
		}

		else if (!client->_connected
				&& (input == "register" || input == "login" || input == "list"
						|| input == "invite" || input == "auto"||input=="records")) {
			onError("please connect to server first [ connect -ip- ]");
		}

		else if (input == "exit") {
			client->disconnect();
			break;
		}

		else if (input == "register") {
			cin >> input;
			client->userRegister(input.c_str());
		} else if (input == "login") {
			cin >> input;
			client->userLogin(input.c_str());
		}

		else if (input == "list")
			client->onlineList();

		else if(input=="records")
			client->recordList();

		else if (input == "auto")
		{
			client->autoMatch();
			gameTryLock=true;
		}

		else if (input == "invite") {
			cin >> input;
			client->invite(input.c_str());
			gameTryLock=true;
		}

		else
			onError("unknown command");

	} //end while
}


///********************
//******handler********
///********************
void ClientCLI::onRecieveMessage(string message) {
	cout << message << endl;
}
void ClientCLI::onError(string error) {
	cerr << error << endl;
}

void ClientCLI::matchOffer(string addr) {
	offer = true;
	offerUname = addr;
	cout << "----------\nmatch offer from " << addr << "\n"
			<< "to accept enter 'yes'\n other to reject" << endl;

}

void ClientCLI::gameStarting(string message) {
	cout<<"Game started"<<endl;
	Player* player;
	if(message.empty())
player=new Host();

	else player=new Guest(message);
int score=player->startGame();
client->gameOver(score);

}
void ClientCLI::gameRejected(string message){
cout<<message<<endl;
delete gameGuard;
}

void ClientCLI::gameOver(string message) {
	cout<<"game over\nyour score: "<<message<<endl;
	delete gameGuard;
}


void ClientCLI::printCommandList() {

	cout << " ---------------------------------------- " << endl;
	cout << "| command name     param1      param2    |" << endl;
	cout << "| --------------   --------    --------- |" << endl;
	cout << "| instructions     ins         --------- |" << endl;
	cout << "| server connect   connect     ip        |" << endl;
	cout << "| register         register    user:pass |" << endl;
	cout << "| login            login       user:pass |" << endl;
	cout << "| online users     list        --------- |" << endl;
	cout << "| record list      records     --------- |" << endl;
	cout << "| send invitation  invite      user      |" << endl;
	cout << "| accept           yes         --------- |" << endl;
	cout << "| auto-match       auto        --------- |" << endl;
	cout << "| exit             exit        --------- |" << endl;
	cout << " ---------------------------------------- " << endl;

}

void ClientCLI::printInstructions() {

	cout << " --------------------------------------------- " << endl;
	cout << "|  Hang Man Instructions                      |" << endl;
	cout << "|  ---------------------                      |" << endl;
	cout << "|  One player thinks of a word of some topic, |" << endl;
	cout << "|  The other tries to guess it by suggesting  |" << endl;
	cout << "|  letters by the topic that the other chose, |" << endl;
	cout << "|  within a certain number of guesses.        |" << endl;
	cout << " --------------------------------------------- " << endl;

}

}

