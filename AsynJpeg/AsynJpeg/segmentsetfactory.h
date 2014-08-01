//
//  segmentsetfactory.h
//  AsynJpeg
//
//  Created by 单杰晶 on 14-7-28.
//  Copyright (c) 2014年 单杰晶. All rights reserved.
//

#ifndef AsynJpeg_segmentsetfactory_h
#define AsynJpeg_segmentsetfactory_h

#include "segmentset.h"

class SegmentSetFactory {
public:
    SegmentSet format(const JpegMarkId markId, const char* data, const int dataLen);
    SegmentSet parse(ifstream& ifs);
};


#endif
