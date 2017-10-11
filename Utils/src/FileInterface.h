

#ifndef SRC_FILEINTERFACE_H_
#define SRC_FILEINTERFACE_H_
#include<iostream>
using namespace std;
namespace npl {

class FileInterface {
public:

	virtual ~FileInterface(){}
	virtual void close()=0;
	virtual int read(char* buffer,int length)=0;
	virtual int write(const char* msg,int length)=0;

};

} /* namespace FileName */

#endif /* SRC_FILEINTERFACE_H_ */
