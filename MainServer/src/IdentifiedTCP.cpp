/*
 * IdentifiedTCP.cpp
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#include "IdentifiedTCP.h"
#include <sstream>
namespace npl {

IdentifiedTCP::IdentifiedTCP(TCPSocket* socket,char* name,int score):TCPSocket(socket->getSocket(), socket->getLocalAddr(), socket->getPeerAddr()){

		this->name=name;
		this->score=score;
		autoMatch=false;
		busy=false;
}
void IdentifiedTCP::updateScore(int x){
	score+=x;
}

char* IdentifiedTCP::getName(){
	return name;
}



void IdentifiedTCP::setAutoMatchStatus(bool b){
autoMatch=b;
}
bool IdentifiedTCP::getAutoMatchStatus(){
return autoMatch;
}
void IdentifiedTCP::setBusyStatus(bool b){
busy=b;
}
bool IdentifiedTCP::getBusyStatus(){
return busy;
}
string IdentifiedTCP::getScore(){
	ostringstream temp;
	temp<<score;
return temp.str();
}

} /* namespace npl */
