#ifndef AD7992_H
#define AD7992_H

#include <QCoreApplication>
#include "ch367.h"

class Ad7992
{
public:
    Ad7992();
    ~Ad7992();
    bool init(CH367* pDev);
//    bool init(I2C* i2c, IO* io);
    bool getValue(quint16* oValue);

private:
    bool initFlag;
    CH367* pCh367;
    //I2C* i2c;
    //IO*   io;
};

//class I2C{
//public:
//    virtual void readI2C() = 0;
//    virtual void writeI2C() = 0;

//};

//class CH367 : public I2C
//{
//public:
//    virtual void readI2C(){
//        //open CH367
//    }
//    virtual void writeI2C(){
//        //close CH367
//    }

//};

//I2C* ic = new CH367()

#endif // AD7992_H
