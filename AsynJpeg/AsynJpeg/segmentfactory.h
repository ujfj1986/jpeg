//
//  segmentfactory.h
//  AsynJpeg
//
//  Created by 单杰晶 on 14-7-28.
//  Copyright (c) 2014年 单杰晶. All rights reserved.
//

#ifndef AsynJpeg_segmentfactory_h
#define AsynJpeg_segmentfactory_h

#include "segment.h"

class SegmentFactory {
public:
    SegmentFactory();
    static Segment* creat(const JpegMarkId markId, ifstream& ifs);
};

#endif
