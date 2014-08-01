/*
 * jpegutil.h
 *
 * Created on 20 July, 2014
 * Author: Jiejing shan
 */

#ifndef _JPEG_UTIL_H_

#define _JPEG_UTIL_H_

#include <string>

using namespace std;

#define G16S(p) (((unsigned char)p[0] << 8) | (unsigned char)p[1])
#define S16S(p, s) { \
	*(p++) = (unsigned char)((s & 0xFF)0) >> 8); \
	*(p++) = (unsigned char)(s & 0x00FF); \
	}

class JpegMarkId {
public:
    
    const static unsigned short JPEG_SOI;
    const static unsigned short JPEG_APP0;
    const static unsigned short JPEG_APP1;
    const static unsigned short JPEG_APP2;
    const static unsigned short JPEG_APP3;
    const static unsigned short JPEG_APP4;
    const static unsigned short JPEG_APP5;
    const static unsigned short JPEG_APP6;
    const static unsigned short JPEG_APP7;
    const static unsigned short JPEG_APP8;
    const static unsigned short JPEG_APP9;
    const static unsigned short JPEG_APP10;
    const static unsigned short JPEG_APP11;
    const static unsigned short JPEG_APP12;
    const static unsigned short JPEG_APP13;
    const static unsigned short JPEG_APP14;
    const static unsigned short JPEG_APP15;
    const static unsigned short JPEG_DQT;
    const static unsigned short JPEG_SOF0;
    const static unsigned short JPEG_DHT;
    const static unsigned short JPEG_DRI;
    const static unsigned short JPEG_SOS;
    const static unsigned short JPEG_DATA;
    const static unsigned short JPEG_EOI;
    const static unsigned short JPEG_INVALID_MARK;
    const static unsigned short JPEG_MAX_MARK;
    
    JpegMarkId(unsigned short markId) {
//        switch (markId) {
//            case 0xFFD8:            //JPEG_SOI
//                markKey = 1;
//                break;
//            case 0xFFE0:            //JPEG_APP0:
//                markKey = 2;
//                break;
//            case 0xFFE1:            //JPEG_APP1:
//                markKey = 3;
//                break;
//            case 0xFFE2:            //JPEG_APP2:
//                markKey = 4;
//                break;
//            case 0xFFE3:            //JPEG_APP3:
//                markKey = 5;
//                break;
//            case 0xFFE4:            //JPEG_APP4:
//                markKey = 6;
//                break;
//            case 0xFFE5:            //JPEG_APP5:
//                markKey = 7;
//                break;
//            case 0xFFE6:            //JPEG_APP6:
//                markKey = 8;
//                break;
//            case 0xFFE7:            //JPEG_APP7:
//                markKey = 9;
//                break;
//            case 0xFFE8:            //JPEG_APP8:
//                markKey = 10;
//                break;
//            case 0xFFE9:            //JPEG_APP9:
//                markKey = 11;
//                break;
//            case 0xFFEA:            //JPEG_APP10:
//                markKey = 12;
//                break;
//            case 0xFFEB:            //JPEG_APP11:
//                markKey = 13;
//                break;
//            case 0xFFEC:            //JPEG_APP12:
//                markKey = 14;
//                break;
//            case 0xFFED:            //JPEG_APP13:
//                markKey = 15;
//                break;
//            case 0xFFEE:            //JPEG_APP14:
//                markKey = 16;
//                break;
//            case 0xFFEF:            //JPEG_APP15:
//                markKey = 17;
//                break;
//            case 0xFFDB:            //JPEG_DQT:
//                markKey = 18;
//                break;
//            case 0xFFC0:            //JPEG_SOF0:
//                markKey = 19;
//                break;
//            case 0xFFC4:            //JPEG_DHT:
//                markKey = 20;
//                break;
//            case 0xFFDD:            //JPEG_DRI:
//                markKey = 21;
//                break;
//            case 0xFFDA:            //JPEG_SOS:
//                markKey = 22;
//                break;
//            case 0xFFFF:            //JPEG_DATA:
//                markKey = 23;
//                break;
//            case 0xFFD9:            //JPEG_EOI:
//                markKey = 24;
//                break;
//                
//            default:
//                markKey = 0;
//                break;
//        }
//        markValue = markId;
        int i = 0;
        for (i = 0; i < (sizeof(MARK_KEY_VALUE_TABLE) / sizeof(Mark)); i++) {
            if (markId == MARK_KEY_VALUE_TABLE[i].value) {
                markKey = MARK_KEY_VALUE_TABLE[i].key;
                markValue = markId;
            }
        }
        if (i == (sizeof(MARK_KEY_VALUE_TABLE) / sizeof(Mark))) {
            markKey = 0;
            markValue = markId;
        }
    }
    
    JpegMarkId(const JpegMarkId& other) {
        markKey = other.markKey;
        markValue = other.markValue;
    }
    
    int getKey() const{
        return markKey;
    }
    
    unsigned short getValue() const{
        return markValue;
    }
    
    bool isValid() {
        return 0 != markKey;
    }
    
    bool operator== (unsigned short value) {
        return this->markValue == value;
    }
    
    bool operator> (unsigned short value) {
        return this->markValue > value;
    }
    
    bool operator < (unsigned short value) {
        return this->markValue < value;
    }
    
    bool operator >= (unsigned short value) {
        return this->markValue >= value;
    }
    
    bool operator <= (unsigned short value) {
        return this->markValue <= value;
    }
    
    JpegMarkId& operator = (const JpegMarkId& other) {
        markKey = other.markKey;
        markValue = other.markValue;
        return *this;
    }
    
private:
    int markKey;
    unsigned short markValue;
    
    struct Mark {
        int key;
        unsigned short value;
        string name;
    };
    const static Mark MARK_KEY_VALUE_TABLE[25];
};


#endif //_JPEG_UTIL_H_
