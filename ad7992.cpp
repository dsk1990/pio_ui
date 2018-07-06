#include <qdebug.h>
#include <qglobal.h>
#include "ad7992.h"
#include "ch367.h"

#define AD7992_CHANNEL_SHIFT	4

#define AD7992_I2C_ADDR         0x21

#define AD7992_CONV_RES_REG		0x0
#define AD7992_ALERT_STAT_REG	0x1
#define AD7992_CONF_REG			0x2
#define AD7992_CYCLE_TMR_REG	0x3

#define AD7992_CONF_REG_VALUE	0X18    //convert on ch1; ref from vdd
#define AD7992_ACTIVE_SCAN_MASK 1       //conversion on ch1;

Ad7992::Ad7992()
    :initFlag(false)
{
//    qDebug() << "ad7992 has being created";
}

Ad7992::~Ad7992(){

}

bool Ad7992::init(CH367* pDev)
{
    pCh367 = pDev;
    if(!pCh367->isOpen()){
        //open device
        bool i = pCh367->openDevice();
        if(!i){
            qDebug("Ad7992 init failed");
            return 0;
        }
    }
    if(!pCh367->writeI2C(AD7992_I2C_ADDR, AD7992_CONF_REG, AD7992_CONF_REG_VALUE)){
//        qDebug() << AD7992_I2C_ADDR << " " << AD7992_CONF_REG << " " << AD7992_CONF_REG_VALUE;
        qDebug("Ad7992 init failed");
        return 0;
    }
    qDebug("Ad7992 init succeed");
    initFlag = 1;
    return 1;
}

bool Ad7992::getValue(quint16* oValue)
{
    if(!initFlag){
        qDebug() << "Ad7992 is not init";
        return 0;
    }

    quint8 convResReg = AD7992_ACTIVE_SCAN_MASK << AD7992_CHANNEL_SHIFT | AD7992_CONV_RES_REG;
    bool i;
    ulong length = 2;
    quint8 readValue[2];
    quint16 tempValue[2];
    memset(readValue, 0,2);
    memset(tempValue, 0,2);

    i = pCh367->readI2CEx(AD7992_I2C_ADDR, convResReg, &length, readValue);

    if(!i){
        qDebug() << "ad7992 getValue error!";
        return 0;
    }

    //Combine 12bit value
    readValue[0] = readValue[0] & 0x0f;
    tempValue [0] = (quint16)readValue[0];
    tempValue [1] = (quint16)readValue[1];
    *oValue = (tempValue[0] << 8) | tempValue[1];

    return i;
}


