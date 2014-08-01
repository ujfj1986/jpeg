/*************************************************************************
    > File Name: segmentinterface.h
    > Author: Jiejing shan
    > Mail: ujfj1986@163.com 
    > Created Time: 五  8/ 1 11:31:05 2014
 ************************************************************************/
#ifndef _SEGMENT_INTERFACE_H_

#define _SEGMENT_INTERFACE_H_

#include<iostream>
#include "jpegutil.h"
using namespace std;

class SegmentInterface {
public:
	virtual SemgnetInterface(const JpegMarkId markId) = 0;
	virtual void getPrivateFlag(const char* flag) = 0;
	//bool isSamePrivateFlag(const char* flag) = 0;
	virtual bool isSameType(const SegmentInterface* other) = 0;
	virtual int parsePrivateFlag(fstream& ifs, const char* flag) = 0;

	virtual JpegMarkId getSegmentMarkId() = 0;
	//void setSegmentMarkId(const JpegMarkId mark) =  0;

	//int getSegmentLength() = 0;
	//void setSegmentLength() = 0;

	virtual int getDataLength() = 0;
	virtual int readData(const char* buffer) = 0;

	virtual int formatData(const char* data, const int dataLen) = 0;
};

#endif //_SEGMENT_INTERFACE_H_
