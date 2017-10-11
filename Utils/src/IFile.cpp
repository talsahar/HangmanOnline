/*
 * File.cpp
 *
 *  Created on: Jun 1, 2017
 *      Author: user
 */

#include "IFile.h"

namespace npl {

IFile::IFile(string fName) {
this->fileName=fName;
}

IFile::~IFile() {
	close();
}

void IFile::close(){
int x=fclose(myFile);

if(x<0){
	perror("No file to close");
	return;
}

}


////fs.open ("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);


int IFile::write(const char* msg,int length){
	cout<<"\nFile opened for writing."<<endl;
cout<<"Writing: "<<msg<<endl;
	myFile=fopen(fileName.data(),"w");
	fprintf(myFile,msg);


return 1;
}

int IFile::read(char* buffer,int length){
	cout<<"\nFile opened for reading."<<endl;


	myFile=fopen(fileName.data(),"r");
	fgets(buffer,length,myFile);

return 1;
}


} /* namespace FileName */
