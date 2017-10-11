/*
 * Player.cpp
 *
 *  Created on: Aug 15, 2017
 *      Author: user
 */

#include "Player.h"

namespace npl {

Player::Player(int localPort) {
	socket = new UDPSocket(localPort);
	playing = false;
	score = 0;

}
 Player::~Player(){
	 if(socket)
	 {
		 socket->close();
		 delete socket;
	 }

 }



bool Player::sendCommand(int command, char* args) {

	char c[1];
	sprintf(c, "%d", command);

	if (send(c) <0){
		onError("Error writing command Integer");
		socket->close();
		return false;
	}

	if (args != NULL)
		if (strlen(args) != 0) {

			if (send(args) < 0) {
				onError("Error writing command argument");
				socket->close();
				return false;
			}
		}
	return true;
}

char* Player::readMessage(char* buffer) {

	int rc = socket->read(buffer, 100);
	if (rc > 0 && rc < 100) {
		buffer[rc] = 0;
		return buffer;
	}

	return NULL;
}

void Player::readWhile() {
playing=true;
	char buffer[100];
	while (playing) {
		if (readMessage(buffer) != NULL)
			analyzeMessage(buffer);

	}
}

void Player::close(){
	playing=false;
	socket->close();
}


void Player::onError(string error){
cerr<<error<<endl;
}


bool Player::retryQ(){
	char c;
	do
	{
		cout<<"Would you like to play again? (Y/N): ";
	       cin >> c;
	}
	while((c !='Y')&&(c !='N')&&(c !='y')&&(c !='n'));
	if (c=='Y'||c=='y')
		return true;
	return false;
}





/////
void Player::printHangedMan(char* status) {
	switch (atoi(status)) {
	case 9:
		manPrinter.hanged9();
		break;
	case 8:
		manPrinter.hanged8();
		break;
	case 7:
		manPrinter.hanged7();
		break;
	case 6:
		manPrinter.hanged6();
		break;
	case 5:
		manPrinter.hanged5();
		break;
	case 4:
		manPrinter.hanged4();
		break;
	case 3:
		manPrinter.hanged3();
		break;
	case 2:
		manPrinter.hanged2();
		break;
	case 1:
		manPrinter.hanged1();
		break;
	case 0:
		manPrinter.hanged0();
		break;
	}

}

} /* namespace npl */
