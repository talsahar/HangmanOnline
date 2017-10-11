/*
 * MainServerTest.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: user
 */

#include "MainServerTest.h"

namespace npl {

void MainServerTest::test(){
MainServer server;
server.start();
char c;
while(true){
	cin>>c;
	if(c=='q')
	{
		server.stop();
		break;
	}
}
sleep(5);
cout<<"Bye"<<endl;
}

} /* namespace npl */
