//
//  jpegutil.cpp
//  AsynJpeg
//
//  Created by 单杰晶 on 14-7-24.
//  Copyright (c) 2014年 单杰晶. All rights reserved.
//

#include "jpegutil.h"


const unsigned short JpegMarkId::JPEG_SOI = 0xFFD8;
const unsigned short JpegMarkId::JPEG_APP0 = 0xFFE0;
const unsigned short JpegMarkId::JPEG_APP1 = 0xFFE1;
const unsigned short JpegMarkId::JPEG_APP2 = 0xFFE2;
const unsigned short JpegMarkId::JPEG_APP3 = 0xFFE3;
const unsigned short JpegMarkId::JPEG_APP4 = 0xFFE4;
const unsigned short JpegMarkId::JPEG_APP5 = 0xFFE5;
const unsigned short JpegMarkId::JPEG_APP6 = 0xFFE6;
const unsigned short JpegMarkId::JPEG_APP7 = 0xFFE7;
const unsigned short JpegMarkId::JPEG_APP8 = 0xFFE8;
const unsigned short JpegMarkId::JPEG_APP9 = 0xFFE9;
const unsigned short JpegMarkId::JPEG_APP10 = 0xFFEA;
const unsigned short JpegMarkId::JPEG_APP11 = 0xFFEB;
const unsigned short JpegMarkId::JPEG_APP12 = 0xFFEC;
const unsigned short JpegMarkId::JPEG_APP13 = 0xFFED;
const unsigned short JpegMarkId::JPEG_APP14 = 0xFFEE;
const unsigned short JpegMarkId::JPEG_APP15 = 0xFFEF;
const unsigned short JpegMarkId::JPEG_DQT = 0xFFDB;
const unsigned short JpegMarkId::JPEG_SOF0 = 0xFFC0;
const unsigned short JpegMarkId::JPEG_DHT = 0xFFC4;
const unsigned short JpegMarkId::JPEG_DRI = 0xFFDD;
const unsigned short JpegMarkId::JPEG_SOS = 0xFFDA;
const unsigned short JpegMarkId::JPEG_DATA = 0xFFFF;
const unsigned short JpegMarkId::JPEG_EOI = 0xFFD9;
const unsigned short JpegMarkId::JPEG_INVALID_MARK = 0xFF00;
const unsigned short JpegMarkId::JPEG_MAX_MARK = 0xFFFF;

const JpegMarkId::Mark JpegMarkId::MARK_KEY_VALUE_TABLE[25] = {
    {1, JpegMarkId::JPEG_SOI, "JPEG_SOI"},
    {2, JpegMarkId::JPEG_APP0, "JPEG_APP0"},
    {3, JpegMarkId::JPEG_APP1, "JPEG_APP1"},
    {4, JpegMarkId::JPEG_APP2, "JPEG_APP2"},
    {5, JpegMarkId::JPEG_APP3, "JPEG_APP3"},
    {6, JpegMarkId::JPEG_APP4, "JPEG_APP4"},
    {7, JpegMarkId::JPEG_APP5, "JPEG_APP5"},
    {8, JpegMarkId::JPEG_APP6, "JPEG_APP6"},
    {9, JpegMarkId::JPEG_APP7, "JPEG_APP7"},
    {10, JpegMarkId::JPEG_APP8, "JPEG_APP8"},
    {11, JpegMarkId::JPEG_APP9, "JPEG_APP9"},
    {12, JpegMarkId::JPEG_APP10, "JPEG_APP10"},
    {13, JpegMarkId::JPEG_APP11, "JPEG_APP11"},
    {14, JpegMarkId::JPEG_APP12, "JPEG_APP12"},
    {15, JpegMarkId::JPEG_APP13, "JPEG_APP13"},
    {16, JpegMarkId::JPEG_APP14, "JPEG_APP14"},
    {17, JpegMarkId::JPEG_APP15, "JPEG_APP15"},
    {18, JpegMarkId::JPEG_DQT, "JPEG_DQT"},
    {19, JpegMarkId::JPEG_SOF0, "JPEG_SOF0"},
    {20, JpegMarkId::JPEG_DHT, "JPEG_DHT"},
    {21, JpegMarkId::JPEG_DRI, "JPEG_DRI"},
    {22, JpegMarkId::JPEG_SOS, "JPEG_SOS"},
    {23, JpegMarkId::JPEG_DATA, "JPEG_DATA"},
    {24, JpegMarkId::JPEG_EOI, "JPEG_EOI"},
    {0, JpegMarkId::JPEG_INVALID_MARK, "JPEG_INVALID_MAR"},
};