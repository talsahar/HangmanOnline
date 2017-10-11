/*
 * GameClientTest.cpp
 *
 *  Created on: Aug 28, 2017
 *      Author: user
 */

#include "GameClientTest.h"

namespace npl {



bool GameClientTest::test() {

	cout<<"****TEST****"<<endl;

	cout<<"Client 1 starts"<<endl;
	GameClient client(this);
	client.connect("127.0.0.1");
//	sleep(1);
//	client.userRegister("new:111");
sleep(1);
	client.userLogin("tal111:111");
	sleep(1);
	client.onlineList();
	sleep(1);
	client.recordList();
	start();
	sleep(4);
	//client.autoMatch();
	client.accept("tal222");
//	client.reject("tal222");
	sleep(5);
	client.gameOver(0);
	sleep(3);
	client.disconnect();
	this->waitForThread();
	return true;
}



void GameClientTest::run(){
		cout<<"Client 2 starts"<<endl;
		GameClient client(this);
		client.connect("127.0.0.1");
		sleep(1);
		client.userLogin("tal222:222");
		sleep(1);
		client.onlineList();
		sleep(1);
		//client.autoMatch();
		client.invite("tal111");
		sleep(5);
		client.gameOver(0);
		sleep(3);
		client.disconnect();
		sleep(3);
}





void GameClientTest::onRecieveMessage(string message) {
	cout << message << endl;
}
void GameClientTest::matchOffer(string addr) {
	cout << "----------\nmatch offer from " << addr << "\n"
				<< "to accept enter 'yes'\n other to reject" << endl;

}
void GameClientTest::gameStarting(string message) {
	cout<<"game started"<<endl;
}
void GameClientTest::onError(string error) {
	cerr << error << endl;
}
void GameClientTest::gameRejected(string message) {
	cout<<"game offer rejected from "<<message<<endl;

}
void GameClientTest::gameOver(string message) {
	cout<<"game over \nscore: "<<message<<endl;

}

} /* namespace npl */
