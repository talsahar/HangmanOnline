/*
 * IdentifiedTCP.h
 *
 *  Created on: Aug 11, 2017
 *      Author: user
 */

#ifndef SRC_IDENTIFIEDTCP_H_
#define SRC_IDENTIFIEDTCP_H_
#include "TCPSocket.h"
namespace npl {

class IdentifiedTCP:public TCPSocket{
		char* name;
		int score;
		bool busy;
		bool autoMatch;
public:

	IdentifiedTCP(TCPSocket* socket,char* name,int score);
	void updateScore(int x);
	string getScore();
	char* getName();
	void setAutoMatchStatus(bool b);
	bool getAutoMatchStatus();
	void setBusyStatus(bool b);
	bool getBusyStatus();
virtual ~IdentifiedTCP(){}

};

} /* namespace npl */

#endif /* SRC_IDENTIFIEDTCP_H_ */
