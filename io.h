#ifndef IO_H
#define IO_H

#include <qglobal.h>
#include <streambuf>

//#define ADDR_LENGTH 256

class IO {
public:
    virtual bool resetIO() = 0;

    virtual bool readIOByte(quint8 addr, quint8* oData) = 0;
    virtual bool readIOBit(quint8 addr, quint8 bitNum, quint8* oData) = 0;

    virtual bool writeIOByte(quint8 addr, quint8 iData) = 0;
    virtual bool writeIOBit(quint8 addr, quint8 bitNum, quint8 iData) = 0;
//    virtual bool readOutputByte(quint8 addr, quint8* oData);
//    virtual bool readOutputBit(quint8 addr, quint8 bitNum, quint8* oData);


//private:
//    quint8 writeDataBuff[ADDR_LENGTH];
}

#endif // IO_H
