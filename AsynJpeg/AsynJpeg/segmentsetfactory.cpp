//
//  segmentsetfactory.cpp
//  AsynJpeg
//
//  Created by 单杰晶 on 14-7-28.
//  Copyright (c) 2014年 单杰晶. All rights reserved.
//

#include "segmentsetfactory.h"

SegmentSet* SegmentSetFactory::format(const JpegMarkId markId, const char* data, const int dataLen) {
    SegmentSet *ret = nullptr;
    
    if (!markId.isValid()) {
        return ret;
    }
    
    return ret;
}