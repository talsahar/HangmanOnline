
#ifndef SRC_IFILE_H_
#define SRC_IFILE_H_
#include"FileInterface.h"
#include<iostream>
#include <stdlib.h>

#include<stdio.h>
using namespace std;


namespace npl{

class IFile:public FileInterface {
protected:
	string fileName;
FILE* myFile;
public:
IFile(string fName);
	virtual ~IFile();
		void close();
		int read(char* buffer,int length);
		int write(const char* msg,int length);
};

} /* namespace FileName */

#endif /* SRC_IFILE_H_ */
