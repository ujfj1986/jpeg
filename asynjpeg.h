/*
 * asynjpeg.h
 *
 * Created on 17 July, 2014
 * Author: Jiejing shan
 */

#ifndef _ASYN_JPEG_H_
#define _ASYN_JPEG_H_

#include <vector>
#include <list>
//#include <pthread>

//#include "segmentset.h"
#include "jpegutil.h"
#include "jpegnode.h"

using namespace std;

class AsynJpeg{
public :
	AsynJpeg(const string file);
	~AsynJpeg();

	//int insert(SegmentSet& set);
	int parse();
	//void getSameMarkIdSegmentSet(JPEG_MARK_ID markId, vector<SegmentSet>& segs);
	int save();
	//int findSegmentSetById(void* id, vector<SegmentSet>& segs);
	//int removeSegmentSet(void* id);
	//int removeAllMarkIdSegmentSet(JPEG_MARK_ID markId);
	//int exchangeImageData(Image *pImage);
    void release();
    int getAppnEndOffset() {
        return mAppnEndOffset;
    }
    int readFrom(const int offset, const char* buffer, const int size);
    int writeTo(const int offset, const char* buffer, const int bufferSize);
    
    //temp api
    void show();
    int insertBuffer(const char* buffer, const int len);
    int removeNodeByMark(JpegMarkId mark);
    
    vector<JpegNode> getNodesByMark(JpegMarkId mark);

private:
    
    int parseFileNode();
    int insertFileNode(JpegNode node);
    int removeFileNode(JpegNode node);
    
    string getTmpFileName();
    
	string mFileName;
	//vector<SegmentSet> mFileStruct;
 	//pthread_rwlock_t mFileStructLock;

	list<JpegNode> mFileNodes;
	int mAppnEndOffset;
	bool mIsExist;
    int mSize;
    bool mIsInvalid;
    int mOldSize;
    bool mIsDirty;
}; 

#endif //_ASYN_JPEG_H_
