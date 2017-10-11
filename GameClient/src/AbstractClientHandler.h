/*
 * AbstractedClientHandler.h
 *
 *  Created on: Aug 17, 2017
 *      Author: user
 */

#ifndef SRC_ABSTRACTCLIENTHANDLER_H_
#define SRC_ABSTRACTCLIENTHANDLER_H_
#include<iostream>
using namespace std;
namespace npl {

class AbstractClientHandler{
public:
//from server
	virtual void onRecieveMessage(string message)=0;
	virtual void matchOffer(string addr)=0;
	virtual void gameStarting(string message)=0;
	virtual void onError(string error)=0;
	virtual void gameRejected(string message)=0;
	virtual void gameOver(string message)=0;
//from client


	virtual ~AbstractClientHandler(){}

};

} /* namespace npl */

#endif /* SRC_ABSTRACTCLIENTHANDLER_H_ */
