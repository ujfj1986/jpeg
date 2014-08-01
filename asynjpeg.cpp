/*
 * asynjpeg.cpp
 *
 * Created on 18 July, 2014
 * Author: Jiejing shan
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <cstdio>

#include "asynjpeg.h"

AsynJpeg::AsynJpeg(string name) {
   	mFileName = name;
	ifstream ifs(name, ios::binary);
	if (ifs.fail()) {
		return ;
	}

	if (!ifs) {
		mIsExist = false;
	} else {
		mIsExist = true;
	}
    ifs.close();
    mAppnEndOffset = 0;
    mSize = 0;
    mOldSize = 0;
    mIsDirty = false;
    mIsInvalid = false;
	parseFileNode();
}

AsynJpeg::~AsynJpeg() {
	
}

void AsynJpeg::release() {
    for (list<JpegNode>::iterator it = mFileNodes.begin();
         it != mFileNodes.end();
         it++) {
        it->release();
    }
}

int AsynJpeg::parseFileNode() {
	if (!mIsExist) {
		return 0;
	}

	ifstream is(mFileName, ios::binary);
	if (is.fail()) {
		return -1;
	}

	char buff[2] = "\0";
	int itag = 0;
	int len = 0;
	int ret = 0;
	int offset = 0;
    JpegNode segNode;
    JpegNode dataNode;
    bool dataStartFlag = false;
    int sosEnd = 0;

	while(!is.eof()) {
		segNode.clear();
		is.read(buff, 2);
		offset += 2;
		itag = G16S(buff);
        
		if (itag == JpegMarkId::JPEG_SOI) {
			segNode.init(JpegMarkId::JPEG_SOI, (offset - 2), 2);
			segNode.setPrivateFlag(&itag, sizeof(itag));
			mAppnEndOffset = offset;
		}  else if ((itag <= JpegMarkId::JPEG_APP15) && (itag >= JpegMarkId::JPEG_APP0)) {
			is.read(buff, 2);
			len = G16S(buff);
            segNode.init(itag, (offset - 2), (len + 2));
            //TODO: get the APPN segment's private flag
            //TODO: set the node's private flag.
            is.seekg(len - 2, ios::cur);
            offset += len;
            mAppnEndOffset = offset;
        } else if ((itag == JpegMarkId::JPEG_DQT) ||
              (itag == JpegMarkId::JPEG_SOF0) ||
              (itag == JpegMarkId::JPEG_DHT) ||
              (itag == JpegMarkId::JPEG_DRI) ||
              (itag == JpegMarkId::JPEG_SOS)){
            is.read(buff, 2);
            len = G16S(buff);
            segNode.init(itag, (offset - 2), (len + 2));
            segNode.setPrivateFlag(&itag, sizeof(itag));
            is.seekg((len - 2), ios::cur);
            offset += len;
            if (itag == JpegMarkId::JPEG_SOS) {
                dataStartFlag = true;
                sosEnd = offset;
            }
        } else if (dataStartFlag && (itag != JpegMarkId::JPEG_EOI)) {
            continue;
        } else if (itag == JpegMarkId::JpegMarkId::JPEG_EOI) {
            segNode.init(JpegMarkId::JPEG_EOI, (offset - 2), 2);
            segNode.setPrivateFlag(&itag, sizeof(itag));
            dataNode.init(JpegMarkId::JPEG_DATA, sosEnd, (offset - 2 - sosEnd));
            dataNode.setPrivateFlag(&JpegMarkId::JPEG_DATA, sizeof(JpegMarkId::JPEG_DATA));
            mSize = offset;
            mOldSize = mSize;
        } else if (itag == JpegMarkId::JPEG_MAX_MARK) {
            is.seekg(-1, ios::cur);
            offset -= 1;
        } else {
            ret = -1;
            break;
        }
        
        if (itag == JpegMarkId::JPEG_EOI) {
            mFileNodes.push_back(dataNode);
            mFileNodes.push_back(segNode);
            break;
        }
        mFileNodes.push_back(segNode);
    }
    
    if (ret != 0) {
        mFileNodes.clear();
        mSize = 0;
        mIsInvalid = true;
        mAppnEndOffset = 0;
        mOldSize = mSize;
    }
    
    is.close();
    return ret;
}

void AsynJpeg::show() {
    cout << " file [" << mFileName << "]" << endl;
    if (!mIsExist) {
        cout << "is not existed" << endl;
        return ;
    }
    if (mIsInvalid) {
        cout << " is not valid" << endl;
        return ;
    }
    
    cout << "file is " << (mIsDirty ? "" : "NOT ") << "Dirty" << endl;
    cout << " file size :" << mSize << ", file old size is " << mOldSize << endl;
    cout << " file appn end at " << mAppnEndOffset << endl;
    for (list<JpegNode>::iterator it = mFileNodes.begin();
         it != mFileNodes.end();
         it++) {
        cout << "\t\t\t [" << setbase(16) << it->mMarkId.getValue() << "]" << endl;
        cout << " start at :0x" << setbase(16) << it->mOffset << "| length :0x" << setbase(16) << it->mNodeLen << endl;
        if (it->mMarkId == JpegMarkId::JPEG_APP3)
            cout << " private flag :" << it->mPrivateFlag << endl;
        else
            cout << " private flag :" << *((int *)(it->mPrivateFlag)) << endl;
        cout << "node is " << (it->mIsDirty? "" : "NOT ") << "Dirty" << endl;
        cout << "node is " << (it->mIsNewNode? "" : "NOT ") << "New node" << endl;
        if (it->mBuffer != NULL) {
            cout << "buffer is " << it->mBuffer << ", buffer length is " << it->mNodeLen << endl;
        }
        
        cout << "\t\t old offset is " << it->mOldOffset << endl;
        
    }
}

/*
 * computeNodeOffset
 *
 * compute offset in the file according jpeg mark id.
 */
//int AsynJpeg::computeNodeOffset(unsigned short markId) {
//    if (markId == JpegMarkId::JPEG_INVALID_MARK || markId == JpegMarkId::JPEG_SOI || markId == JpegMarkId::JPEG_EOI) {
//        return -1;
//    }
//    
//    if (markId <= JpegMarkId::JPEG_APP15 && markId >= JpegMarkId::JPEG_APP0) {
//        for (LIST<Jpegnode>::iterator it = mFileNodes.begin(); it != mFileNodes.end(); it++) {
//            if (it->mMarkId > markId || it->mNewOffset == mAppnEndOffset) {
//                break;
//            }
//        }
//        if (it->mNewOffset == mAppnEndOffset) {
//            return mAppnEndOffset;
//        }  else {
//            return it->mNewOffset;
//        }
//    }
//    
//    if (markId == JpegMarkId::JPEG_DQT) {
//        <#statements#>
//    }
//}

/*
 * insertFileNode
 *
 * insert new file node to the file node list, the position is at the @offset of file,
 * modify offset of all the file node which is behand @offset, and mark them new.
 * mark this file as dirty, and compute the file new size.
 */
int AsynJpeg::insertFileNode(JpegNode node) {
    list<JpegNode>::iterator it = mFileNodes.begin();
    while (it != mFileNodes.end()) {
        if (*it > node)
            break;
        it++;
    }
    if (it == mFileNodes.end()) {
        cout << "can't find the insert offset @" << node.mMarkId.getValue() << ", there must be something wrong." << endl;
        return -1;
    }
    //mFileNodes.insert(it, newNode);
    list<JpegNode>::iterator insert = it;
    int offset = insert->mOffset;
    while (it != mFileNodes.end()) {
        it->mOffset += node.mNodeLen;
        it->mIsDirty = true;
        it++;
    }
    if ((node.mMarkId.getValue() >= JpegMarkId::JPEG_APP0) && (node.mMarkId.getValue() <= JpegMarkId::JPEG_APP15)) {
        mAppnEndOffset += node.mNodeLen;
    }
    node.mOffset = offset;
    node.mOldOffset = 0;
    mFileNodes.insert(insert, node);
    mIsDirty = true;
    mSize += node.mNodeLen;
    return 0;
}

/*
 * removeFileNode
 *
 * remove a file node at the @offset of file,
 * modify offset of all file nodes which is behand @offset,
 * mark this file as dirty, and compute the file new size.
 */
int AsynJpeg::removeFileNode(JpegNode node) {
    for ( int i = 0; i < mFileNodes.size(); i ++) {
        list<JpegNode>::iterator it = mFileNodes.begin();
        for (; it != mFileNodes.end(); it++) {
            if (*it == node) {
                break;
            }
        }
        if (it == mFileNodes.end()) {
            cout << "con't find the remove file node at " << node.mMarkId.getValue() << endl;
            return 0;
        }
    
        list<JpegNode>::iterator rem = it;
        for (it++; it != mFileNodes.end(); it++) {
            it->mOffset -= rem->mNodeLen;
            it->mIsDirty = true;
        }
        if ((rem->mMarkId.getValue() >= JpegMarkId::JPEG_APP0) && (rem->mMarkId.getValue() <= JpegMarkId::JPEG_APP15)) {
            mAppnEndOffset -= rem->mNodeLen;
        }
        rem->release();
        mFileNodes.erase(rem);
        mIsDirty = true;
        mSize -= rem->mNodeLen;
    }
    return 0;
}

/*int AsynJpeg::insert(SegmentSet& seg) {
    if (mIsExist) {
        int seglen = seg.getBufferLength();
        JpegNode segNode;
        segNode.init(seg.getMarkId(), mAppnEndOffset, seglen);
        segNode.setNewBuffer(seg.getBuffer(), seglen);
        segNode.setPrivateFlag(seg.getPrivateFlag(), seg.getPrivateFlagLength());
        insertFileNode(mAppnEndOffset, segNode);
    }
}*/

string AsynJpeg::getTmpFileName() {
    string tmp = mFileName;
    return tmp.insert(tmp.find_last_of("."), "_tmp");
}

static void inline copyDataToNewFile(ifstream& ifs, const int readOffset, const int size, fstream& ofs, const int writeOffset) {
    char *buffer = new char[size];
    ifs.seekg(readOffset, ios::beg);
    ifs.read(buffer, size);
    //ofs.seekg(writeOffset, ios::beg);
    ofs.write(buffer, size);
    delete buffer;
}


//TODO: remember write to offset and change write method to multi thread.
int AsynJpeg::save() {
    if (!mIsDirty) {
        return 0;
    }
    
    int ret = 0;
    string tmpFile = getTmpFileName();
    ifstream ifs(mFileName, ios::binary);
    fstream ofs(tmpFile, ios::binary | ios::out);
    if (!ifs || !ofs || ifs.fail() || ofs.fail()) {
        cout << "con't create temp file!" << endl;
        return -1;
    }
    
    int provNodeFlag = 0; //0 is clean; 1 is new; 2 is dirty
    int readOffset = 0;
    int writeToOffset = 0;
    int wantToWriteBytes = 0;
    
    try {
        for (list<JpegNode>::iterator it = mFileNodes.begin();
             it != mFileNodes.end();
             it++) {
            if (!it->mIsDirty) {                        // current node is clean, must be hander of file
                provNodeFlag = 0;
                wantToWriteBytes += it->mNodeLen;            //compute want to write bytes until node is not clean
            } else if (!it->mIsNewNode) {
                if (provNodeFlag == 0) {
                    if (wantToWriteBytes != 0) {
//                        char *buffer = new char[wantToWriteBytes];
//                        ifs.seekg(startOffset, ios::beg);
//                        ifs.read(buffer, wantToWriteBytes);
//                        ofs.write(buffer, wantToWriteBytes);
//                        delete buffer;
                        copyDataToNewFile(ifs, readOffset, wantToWriteBytes, ofs, writeToOffset);
                    }
                    readOffset = it->mOldOffset;
                    wantToWriteBytes = it->mNodeLen;
                } else if (provNodeFlag == 1) {
                    readOffset = it->mOldOffset;
                    wantToWriteBytes = it->mNodeLen;
                } else {
                    if ((readOffset + wantToWriteBytes) == it->mOldOffset) {
                        wantToWriteBytes += it->mNodeLen;
                    } else {
//                        char *buffer = new char[wantToWriteBytes];
//                        ifs.seekg(startOffset, ios::beg);
//                        ifs.read(buffer, wantToWriteBytes);
//                        ofs.write(buffer, wantToWriteBytes);
//                        delete buffer;
                        copyDataToNewFile(ifs, readOffset, wantToWriteBytes, ofs, writeToOffset);
                        readOffset = it->mOldOffset;
                        wantToWriteBytes = it->mNodeLen;
                    }
                }
                provNodeFlag = 2;
            } else {
                if ((provNodeFlag == 0) || (provNodeFlag == 2)) {
                    if (wantToWriteBytes != 0) {
//                        char *buffer = new char[wantToWriteBytes];
//                        ifs.seekg(startOffset, ios::beg);
//                        ifs.read(buffer, wantToWriteBytes);
//                        ofs.write(buffer, wantToWriteBytes);
                        copyDataToNewFile(ifs, readOffset, wantToWriteBytes, ofs, writeToOffset);
                    }
                    readOffset = 0;
                    wantToWriteBytes = 0;
                }
                //ofs.seekg(writeToOffset, ios::beg);
                ofs.write(it->mBuffer, it->mNodeLen);
                provNodeFlag = 1;
            }
        }
        if (wantToWriteBytes != 0) {
//            char *buffer = new char[wantToWriteBytes];
//            ifs.seekg(readOffset, ios::beg);
//            ifs.read(buffer, wantToWriteBytes);
//            ofs.write(buffer, wantToWriteBytes);
            copyDataToNewFile(ifs, readOffset, wantToWriteBytes, ofs, writeToOffset);
            wantToWriteBytes = 0;
            readOffset = 0;
        }
    } catch (exception e) {
        cout << "there is some exception!" << endl;
        ret = -1;
    }
    ifs.close();
    ofs.close();
    
    ret = remove(mFileName.c_str());
    ret = rename(tmpFile.c_str(), mFileName.c_str());
    if (ret == 0) {
        mOldSize = mSize;
        mIsDirty = false;
        for (list<JpegNode>::iterator it = mFileNodes.begin();
             it != mFileNodes.end(); it ++) {
            it->afterSave();
        }
    }
    return ret;
}

//temp api
int AsynJpeg::insertBuffer(const char* buffer, const int len) {
    if (!mIsExist || mIsInvalid) {
        return -1;
    }
    
    JpegNode node;
    node.init(JpegMarkId::JPEG_APP3, 0, 0);
    node.setNewBuffer((char *)buffer, len);
    node.setPrivateFlag((const void *)&JpegMarkId::JPEG_APP3, sizeof(JpegMarkId::JPEG_APP3));
    
    int ret = insertFileNode(node);
    return ret;
}

int AsynJpeg::removeNodeByMark(JpegMarkId mark) {
    if (!mIsExist || mIsInvalid) {
        return -1;
    }
    
    JpegNode node;
    node.init(mark, 0, 0);
    node.setPrivateFlag((const void*)&JpegMarkId::JPEG_APP3, sizeof(JpegMarkId::JPEG_APP3));
    
    int ret = removeFileNode(node);
    return ret;
}





