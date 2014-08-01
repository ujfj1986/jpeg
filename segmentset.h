/*
 * segmentset.h
 *
 * Created on 18 July, 2014
 * Author: Jiejing shan
 */

#ifndef _SEGMENT_SET_H_
#define _SEGMENT_SET_H_

#include "jpegutil.h"
#include "jpegnode.h"

/**
 * class SegmentSet
 * 
 * define a set of segment which have the same private
 * flag .
 */
class SegmentSet {

public:
	SegmentSet();
	~SegmentSet();
	
    int getFileOffset() = 0;
	void setFileOffset(int offset) = 0;
	char* getData() = 0;
	int getDataLength() = 0;
	char* getBuffer() = 0;
	int getBufferLength() = 0;

	int getSegmentSetMarkId() = 0;
	void setSegmentSetMarkId() = 0;

	int format(char* data, int len) = 0;
	int parse(ifstream ifs) = 0;

	void* getPrivateFlag() = 0;
	void setPrivateFlag(void* flag) = 0;
	int getPrivateFlagLength() = 0;
    bool isSamePrivateFlag(void* flag) = 0;

	void release() = 0;

	bool isValidSegmentSet() = 0;

private:

	JpegMarkId mMarkId;
	int mLength;
	char mPrivateFlag[JPEG_NODE_PRIVATE_FLAG_LEN];

};

#endif //_SEGMENT_SET_H_
