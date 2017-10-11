/*
 * Authentication.cpp
 *
 *  Created on: Aug 10, 2017
 *      Author: user
 */

#include "Authentication.h"
#include <fstream>
#include "string.h"
namespace npl {

Authentication::Authentication(string fname) :
		IFile(fname) {}
void Authentication::loadRecords(RecordList* recordList){
	//initialize recordList
		myFile = fopen(fileName.data(), "r");
			if (myFile != NULL){
				char line[256];
				char* user;
				char* score;
				while (fgets(line, sizeof(line), myFile)) {
					user = strtok(line, ":");
					strtok(NULL, ":");
					score = strtok(NULL, ":");
					recordList->add(user, atoi(score));
				}close();
			}
}

int Authentication::userRegister(char* user, char* pass) {

	if (!legalArguments(user, pass))
		return -1;

	if (isExists(user))
		return -2;

	myFile = fopen(fileName.data(), "a");

	fprintf(myFile, user);

	fprintf(myFile, ":");

	fprintf(myFile, hash_str(pass));

	fprintf(myFile, ":0\n");

	close();
	return 0;
}

int Authentication::userLogin(char* user, char* pass) {

	if (!legalArguments(user, pass))
		return -4;

	if (!isExists(user))
		return -1;

	myFile = fopen(fileName.data(), "r");
	if (myFile == NULL)
		return -3;

	char line[256];
	char* pch;
	while (fgets(line, sizeof(line), myFile)) {
		pch = strtok(line, ":");
		if (strcmp(pch, user) == 0) //compare uname
				{

			pch = strtok(NULL, ":");

			if (strcmp(pch, hash_str(pass)) == 0) //compare pass
					{
				pch = strtok(NULL, ":");
				close();
				return atoi(pch);
			} else {
				close();
				return -2;
			}
		}

	}
	close();

	return -1;

}

bool Authentication::isExists(char* user) {

	user = appendCharToCharArray(user, ':');
	myFile = fopen(fileName.data(), "r");
	if (myFile == NULL) {
		cout << "couldn't open for reading" << endl;
		return false;
	}

	char line[256];
	while (fgets(line, sizeof(line), myFile)) {
		size_t lenuser = strlen(user), lenline = strlen(line);
		if (lenuser < lenline) {
			if (strncmp(user, line, lenuser) == 0) {
				close();
				return true;
			}

		}
	}

	close();
	return false;
}

char* Authentication::appendCharToCharArray(char* array, char a) {
	size_t len = strlen(array);
	char* ret = new char[len + 1];
	strcpy(ret, array);
	ret[len] = a;
	ret[len + 1] = '\0';
	return ret;
}

const char* Authentication::hash_str(const char* s) {
	unsigned h = 37;
	while (*s) {
		h = (h * 54059) ^ (s[0] * 76963);
		s++;
	}
	h = h % 86969;

	stringstream strs;
	strs << h;
	string temp_str = strs.str();
	char const* pchar = temp_str.c_str();

	return pchar;
}

bool Authentication::legalArguments(char* user, char* pass) {
	if (user == NULL || pass == NULL)
		return false;

	if (strcmp(user, "") == 0 || strcmp(pass, "") == 0)
		return false;
	return true;
}

void Authentication::updateScore(char* name, char* score) {

	string line;
	ifstream fin;
	fin.open(fileName.c_str());
	ofstream temp;
	temp.open("temp.txt");
	char complete[64];
	bool b = false;
	while (getline(fin, line)) {
		if (strncmp(line.c_str(), name, strlen(name)) == 0) {

			int i = 0;
			for (i = 0; i < line.length(); i++) {
				if (b == false && line[i] == ':')
					b = true;
				else if (b == true && line[i] == ':') {
					i++;
					strncpy(complete, line.c_str(), i);
					complete[i] = 0;

					strcat(complete, score);
					temp << complete << endl;
					break;

				}
			}
		}
		if (b == false) {
			temp << line << endl;
		} else
			b = false;

	}

	temp.close();
	fin.close();
	remove("users.txt");
	rename("temp.txt", "users.txt");

}

} /* namespace npl */
