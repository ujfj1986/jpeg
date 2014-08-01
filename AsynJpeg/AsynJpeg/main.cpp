//
//  main.cpp
//  AsynJpeg
//
//  Created by 单杰晶 on 14-7-19.
//  Copyright (c) 2014年 单杰晶. All rights reserved.
//

#include <iostream>

#include "asynjpeg.h"

#define FILENAME "/Users/shjj/workspace/newJpeg/AsynJpeg/1.jpg"

int main(int argc, const char * argv[])
{

    // insert code here...
    //std::cout << "Hello, World!\n";
    AsynJpeg jpeg(FILENAME);
    
    jpeg.show();
    
    char *buffer = new char [10];
    for (int i = 0; i < 10; i++) {
        buffer[i] = 'a' + i;
    }
    
    cout << "-------------------start to insert a buffer " << endl;
    jpeg.insertBuffer(buffer, 10);
    jpeg.show();
    cout << "-------------------end to show after insert a buffer" << endl;
    
    cout << "-------------------start to save file" << endl;
    jpeg.save();
    jpeg.show();
    cout << "-------------------end to show after save" << endl;
    
    cout << "-------------------start to remove a jpeg app3 node " << endl;
    
    jpeg.removeNodeByMark(JpegMarkId(JpegMarkId::JPEG_APP3));
    jpeg.show();
    
    cout << "------------------end to show after remove app3 node" << endl;
    
    jpeg.save();
    
    jpeg.release();
    return 0;
}

