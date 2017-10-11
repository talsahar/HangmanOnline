/*
 THA  * Host.cpp
 *
 *  Created on: Aug 15, 2017
 *      Author: user
 */

#include "Host.h"
#include "string.h"
namespace npl {

Host::Host() :
		Player(HOST_PORT) {
	guestLife = 10;
}
Host::~Host() {

}

int Host::startGame() {

	readWhile();
	close();
	return score;
}

void Host::analyzeMessage(char* msg) {
	char tmpchar[100];
	switch (atoi(msg)) {

	//game start
	case GUEST_SAY_HELLO:
		guestLife = 10;

		sendCommand(TOPIC_AND_WORD, getTopicAndWord());
		break;

		//game over
	case GUEST_SAY_BYE:
		cout << "--------\nguest left!\n--------" << endl;
		playing = false;
		break;

		//guess
	case GUESS:
		bool result = checkGuessValid(readMessage(tmpchar));
		if (result == true) {
			sendCommand(CORRECT_GUESS, NULL);
			if (checkGuestWin())
			{
				sendCommand(WIN, buildMessage()); //won
				cout<<"you lose"<<endl;
			}
			//retry
			else
				sendCommand(TOPIC_AND_WORD, buildMessage());		//keep guess

		} else {
			guestLife--;
			if (guestLife == 0) {
				score++;
				sendCommand(LOSE, word);
				cout<<"you won!"<<endl;
			} else {
				char c[1];
				sprintf(c, "%d", guestLife);
				sendCommand(BAD_GUESS, c);
				sendCommand(TOPIC_AND_WORD, buildMessage());
			}

			//lose
		}
		break;

	}
	//////////////////////////////////////////////////////////////

}

bool Host::checkGuestWin() {
	for (int i = 0; i < strlen(secret); i++)
		if (secret[i] == '_')
			return false;
	return true;

}

bool Host::checkGuessValid(char* guess) {
	char c = guess[0];
	bool b = false;
	for (int i = 0; i < strlen(word); i++)
		if (word[i] == c && secret[i] == '_') {
			{
				secret[i] = c;
				b = true;
			}
		}
	return b;

}

char* Host::getTopicAndWord() {
	memset(&topic, 0, sizeof(topic));
	memset(&word, 0, sizeof(word));
	memset(&secret, 0, sizeof(secret));
	cout << "----------" << endl;
	cout << "enter topic: ";
	cin >> topic;
	cout << "enter secret word: ";
	cin >> word;

	int i = 0;
	for (i = 0; i < strlen(word); i++)
		secret[i] = '_';

	return buildMessage();
}

char* Host::buildMessage() {
	char* buff = new char[strlen(topic) + strlen(secret) + 2];
	strcpy(buff, topic);
	char c = ',';
	strncat(buff, &(c), 1);
	strcat(buff, secret);

	return buff;
}

int Host::send(string msg) {
	return socket->reply(msg);
}

} /* namespace npl */
