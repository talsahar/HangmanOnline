/*
 * RecordList.cpp
 *
 *  Created on: Aug 21, 2017
 *      Author: user
 */

#include "RecordList.h"

namespace npl {



void RecordList::add(string user,int record){
	//if exists change just value
	map<string, int>::iterator it = myMap.find(user);
	  if (it != myMap.end())
		 it->second=record;
	  //not exists-> add it
	  else
		  myMap[user]=record;

}





string RecordList::getFullRecordList(){
	vector<pair<string,int> > myVec(myMap.begin(), myMap.end());
	sort(myVec.begin(),myVec.end(),sort_pair_second<string,int>());

	std::stringstream message;
	message<<"Score Board:\n------------\n";
	int i=1;
	for(std::vector<pair<string,int> >::iterator it = myVec.begin(); it != myVec.end(); ++it) {
		message<<"#"<<i<<"\t";
		message<<(*it).first<<"\t\t";
		message<<"Score: "<< (*it).second<<"\n";

i++;
		}
return message.str();
}



} /* namespace npl */
