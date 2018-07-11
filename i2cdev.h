#ifndef I2CDEV_H
#define I2CDEV_H

#include <qglobal.h>

//#define i2c_baudrate 400000
//uint32_t i2c_baudrate = 400000 ; //400 kHz,

class I2Cdev {
public:
//    virtual void initialize();
//    virtual void enable(bool isEnabled);

    virtual bool readI2CByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data) = 0;
    virtual bool readI2CWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data) = 0;
    virtual bool readI2CBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) = 0;
    virtual bool readI2CWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data) = 0;

    virtual bool writeI2CByte(uint8_t devAddr, uint8_t regAddr, uint8_t data) = 0;
    virtual bool writeI2CWord(uint8_t devAddr, uint8_t regAddr, uint16_t data) = 0;
    virtual bool writeI2CBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) = 0;
    virtual bool writeI2CWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data) = 0;
};


#endif // I2CDEV_H
