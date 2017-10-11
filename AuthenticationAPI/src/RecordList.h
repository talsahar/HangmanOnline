/*
 * RecordList.h
 *
 *  Created on: Aug 21, 2017
 *      Author: user
 */

#ifndef SRC_RECORDLIST_H_
#define SRC_RECORDLIST_H_
#include <map>
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;
namespace npl {


//comparator
template <class T1, class T2, class Pred = std::less<T2> >
struct sort_pair_second {
    bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
        Pred p;
        return p(right.second, left.second);
    }
};




class RecordList {

	map<string,int> myMap;



public:
	void add(string user,int record);
	string getFullRecordList();
	bool myFunction(pair<string,int> first, pair<string,int> second);


};

} /* namespace npl */

#endif /* SRC_RECORDLIST_H_ */
