/*
 * Guest.cpp
 *
 *  Created on: Aug 15, 2017
 *      Author: user
 */

#include "Guest.h"

namespace npl {

Guest::Guest( string peerIP) :
		Player(GUEST_PORT) {
	this->peerIP = peerIP;
	this->peerPort = HOST_PORT;

}

Guest::~Guest(){

}

int Guest::startGame() {

	if(!sendCommand(GUEST_SAY_HELLO, NULL))
	{
		onError("couldnt connect: host is not available");
		return 0;
	}
	cout<<"waiting for hosts secret.."<<endl;
	readWhile();
	close();
	return score;
}

void Guest::analyzeMessage(char* msg) {
	bool booli;
	char tmpchar[100];
	char* c;
	switch (atoi(msg)) {
	case TOPIC_AND_WORD:
		printTopic(readMessage(tmpchar));
		c=getValidGuess();
		if(c[0]=='0')
			sendCommand(GUEST_SAY_BYE, NULL);
		else
		sendCommand(GUESS, c);
		break;
	case CORRECT_GUESS:
		cout<<"correct guess :)"<<endl;;
		break;
	case BAD_GUESS:
		cout<<"incorrect guess :("<<endl;
		printHangedMan(readMessage(tmpchar));
		break;
	case WIN:
		score++;
		booli = onGameOver(1,readMessage(tmpchar));
		if (booli == true)
			sendCommand(GUEST_SAY_HELLO, NULL);
		else {
			playing = false;
			sendCommand(GUEST_SAY_BYE, NULL);
		}
		break;
	case LOSE:

		booli =onGameOver(0,readMessage(tmpchar));
		if (booli == true)
			sendCommand(GUEST_SAY_HELLO, NULL);
		else {
			playing = false;
			sendCommand(GUEST_SAY_BYE, NULL);
		}
		break;

	}
}

char* Guest::getValidGuess() {

	char tmpchar;
	do {
		cout << "enter guess: ";
			cin >> tmpchar;
	} while ((tmpchar<'a'||tmpchar>'z')&&tmpchar!='0');
char* arr=new char[1];
arr[0]=tmpchar;
return arr;
}

int Guest::send(string msg) {
	return socket->write(msg, peerIP, peerPort);

}

void Guest::printTopic(char* str) {

	char* topic = strtok(str, ",");
	char* word = strtok(NULL, ",");


	cout << "-------" << endl;
	cout << "topic: " << topic << endl;
	cout << "secret: ";
	for(int i=0;i<strlen(word);i++)
		cout<<word[i]<<" ";

	cout<<endl<<"-------"<<endl;

}


bool Guest::onGameOver(bool won,string message) {
if(won)
	manPrinter.hangedwinner();
else
	manPrinter.hanged0();
	cout <<"The word was: "<< message << endl;
	return retryQ();
}

} /* namespace npl */
