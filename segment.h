//
//  segment.h
//  AsynJpeg
//
//  Created by 单杰晶 on 14-7-21.
//  Copyright (c) 2014年 单杰晶. All rights reserved.
//

#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#include <fstream>

class Segment {
public:
    Segment(const JPEG_MARK_ID markId, const int len) : mMarkId(markId), mLength(len) {
        
    }
    ~Segment();
    
    static int parsePrivateFlag(ifstream is, const char* flag) = 0;
    
    int format(const char* buffer, const char* data, const int len) = 0;
    int parse(char* buffer) = 0;
    
private:
    JPEG_MARK_ID mMarkId;
    int mLength;
};

#endif //_SEGMENT_H_
