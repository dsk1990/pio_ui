#ifndef IO_H
#define IO_H

#include <qglobal.h>
#include <streambuf>

//#define ADDR_LENGTH 256

class IO {
public:
    virtual bool reset();

    virtual bool readInputByte(quint8 addr, quint8* oData);
    virtual bool readInputBit(quint8 addr, quint8 bitNum, quint8* oData);

    virtual bool writeOutputByte(quint8 addr, quint8 iData);
    virtual bool writeOutputBit(quint8 addr, quint8 bitNum, quint8 iData);
//    virtual bool readOutputByte(quint8 addr, quint8* oData);
//    virtual bool readOutputBit(quint8 addr, quint8 bitNum, quint8* oData);


//private:
//    quint8 writeDataBuff[ADDR_LENGTH];
}

#endif // IO_H
