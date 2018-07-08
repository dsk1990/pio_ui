#ifndef I2CDEV_H
#define I2CDEV_H

#include <qglobal.h>

//#define i2c_baudrate 400000
//uint32_t i2c_baudrate = 400000 ; //400 kHz,

class I2Cdev {
public:
//    virtual void initialize();
//    virtual void enable(bool isEnabled);

    virtual bool readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data) ＝ 0;
    virtual bool readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data);
    virtual bool readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
    virtual bool readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data);

    virtual bool writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
    virtual bool writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data);
    virtual bool writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
    virtual bool writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data);
};


#endif // I2CDEV_H
