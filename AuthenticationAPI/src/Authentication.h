/*
 * Authentication.h
 *
 *  Created on: Aug 10, 2017
 *      Author: user
 */

#ifndef SRC_AUTHENTICATION_H_
#define SRC_AUTHENTICATION_H_
#include<iostream>
#include "IFile.h"
#include <sstream>
#include <string.h>
#include "RecordList.h"
namespace npl {
//username:password:score



class Authentication:public IFile{


	const char* hash_str(const char* s);
	char* appendCharToCharArray(char* array,char a);
	bool isExists(char* user);
	bool legalArguments(char* user,char* pass);
public:

	Authentication(string fname);
	void loadRecords(RecordList* recordList);
	int userLogin(char* user,char* pass);//return :-1 not exists,-2 incorrect password,-3 fileNotOpen,-4 illegal args, 0+ score (succeed)
	int userRegister(char* user,char* pass);//return :-1 illegal args, -2 exists user, 0 register succeed
	void updateScore(char* name,char* score);



};

} /* namespace npl */

#endif /* SRC_AUTHENTICATION_H_ */
