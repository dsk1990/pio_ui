#ifndef IO_H
#define IO_H

#include <qglobal.h>
#include <streambuf>

#define ADDR_LENGTH 256

class IO {
public:
    virtual bool readByte(quint8 addr, quint8* oData);
    virtual bool readBit(quint8 addr, quint8 bitNum, quint8* oData);

    virtual bool writeByte(quint8 addr, quint8 iData);
    virtual bool writeBit(quint8 addr, quint8 bitNum, quint8 iData);

private:
    quint8 writeDataBuff[ADDR_LENGTH];
}

#endif // IO_H
