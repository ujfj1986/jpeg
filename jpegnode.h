/*************************************************************************
    > File Name: jpegnode.h
    > Author: Jiejing shan
    > Mail: ujfj1986@163.com 
    > Created Time: 四  7/24 15:51:06 2014
 ************************************************************************/

#ifndef _JPEG_NODE_H_

#define _JPEG_NODE_H_

#include <string>

using namespace std;

#define JPEG_NODE_PRIVATE_FLAG_LEN 64

class JpegNode {
    
public:
    JpegMarkId mMarkId;
    int mOffset;
    int mNodeLen;
    bool mIsDirty;
    int mOldOffset;
    char* mBuffer;
    bool mIsNewNode;
    char mPrivateFlag[JPEG_NODE_PRIVATE_FLAG_LEN];
    
    void init(const JpegMarkId markId,
                  const int offset,
                  const int len) {
        clear();
        mMarkId = markId;
        mOffset = offset;
        mNodeLen = len;
        mOldOffset = mOffset;
    }
    
    void init(const JpegMarkId markId,
              char* buffer,
              const int bufferLen) {
        clear();
        mMarkId = markId;
        mNodeLen = bufferLen;
        mBuffer = buffer;
        mIsNewNode = true;
        mIsDirty = true;
    }
    
    void setMarkId(const unsigned short markId) {
        mMarkId = JpegMarkId(markId);
    }
    
    void setOffset(const int offset) {
        mOffset = offset;
    }
    
    void setNewBuffer(char* buffer, const int len) {
        
        mBuffer = buffer;
        mNodeLen = len;
        mIsNewNode = true;
        mIsDirty = true;
    }
    
    int setPrivateFlag(const void* flag, const int len) {
        
        if ((len > JPEG_NODE_PRIVATE_FLAG_LEN) || (len < 0)) {
            
            return -1;
        }
        
        if (((len != 0) && (flag == NULL)) ||
            ((len == 0) && (flag != NULL))) {
            
            return -1;
        }
        if (len != 0) {
            
            memcpy(mPrivateFlag, flag, len);
        }
        return 0;
    }
//    JpegNode() : mMarkId(JpegMarkId::JPEG_INVALID_MARK),
//    mOffset(0), mNodeLen(0), mIsDirty(false), mNewOffset(0),
//    mBuffer(NULL),  mIsNewNode(false) {
//
//        memset(mPrivateFlag, 0, sizeof(mPrivateFlag));
//    }
    
    JpegNode(const unsigned short markId = JpegMarkId::JPEG_INVALID_MARK) : mMarkId(markId),
    mOffset(0), mNodeLen(0), mIsDirty(false), mOldOffset(0),
    mBuffer(NULL),  mIsNewNode(false) {
        
        memset(mPrivateFlag, 0, sizeof(mPrivateFlag));
    }
    
    JpegNode(const JpegNode& other) : mMarkId (other.mMarkId) {
        mOffset = other.mOffset;
        mOldOffset = other.mOldOffset;
        mNodeLen = other.mNodeLen;
        mIsDirty = other.mIsDirty;
        mIsNewNode = other.mIsNewNode;
        mBuffer = other.mBuffer;
        memcpy(mPrivateFlag, other.mPrivateFlag, sizeof(mPrivateFlag));
    }
    
    ~JpegNode() {
        
    }
    
    //must notify; this method don't free mBuffer.
    void clear() {
    
        mMarkId = JpegMarkId::JPEG_INVALID_MARK;
        mOffset = 0;
        mNodeLen = 0;
        mIsDirty = false;
        mOldOffset = 0;
        mBuffer = NULL;
        mIsNewNode = false;
        memset(mPrivateFlag, 0 ,sizeof(mPrivateFlag));
    }
    
    // this method free mBuffer;
    void afterSave() {
        mIsDirty = false;
        mIsNewNode = false;
        if (!mBuffer) {
            delete [] mBuffer;
            mBuffer = NULL;
        }
        mOldOffset = mOffset;
    }
    
    void release() {
        
        if (mBuffer != NULL) {
            
            delete mBuffer;
            mBuffer = NULL;
        }
        memset(mPrivateFlag, 0, sizeof(mPrivateFlag));
    }
    
    bool operator == (const JpegNode& other) {
        if ((mMarkId.getValue() == other.mMarkId.getValue()) &&
            (0 == memcmp(mPrivateFlag, other.mPrivateFlag, sizeof(mPrivateFlag)))) {
            
            return true;
        }
        return false;
    }
    
    bool operator > (const JpegNode& other) {

        return mMarkId.getKey() > other.mMarkId.getKey();
    }
    
    bool operator < (const JpegNode& other) {
        
        return mMarkId.getKey() < other.mMarkId.getKey();
    }
    
    bool operator >= (const JpegNode& other) {
        
        return mMarkId.getKey() >= other.mMarkId.getKey();
    }
    
    bool operator <= (const JpegNode& other) {
        
        return mMarkId.getKey() <= other.mMarkId.getKey();
    }
    
    JpegNode& operator = (const JpegNode& other) {
        mMarkId = other.mMarkId;
        mOffset = other.mOffset;
        mNodeLen = other.mNodeLen;
        mIsDirty = other.mIsDirty;
        mOldOffset = other.mOldOffset;
        mBuffer = other.mBuffer;
        mIsNewNode = other.mIsNewNode;
        memcpy(mPrivateFlag, other.mPrivateFlag, sizeof(mPrivateFlag));
        return *this;
    }
    
} ;


#endif //_JPEG_NODE_H_
