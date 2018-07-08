#ifndef CH367_H
#define CH367_H

#include "CH367DLL.H"
#include <Windows.h>

//CH367
class CH367
{
public:
    CH367();
    ~CH367();

    BOOL    openDevice();
    VOID    closeDevice();              // 关闭CH367设备
    BOOL    isOpen();
//    BOOL    isready();
    HANDLE  getHandle();

    BOOL    readI2C(                    // 从I2C接口读取一个字节数据
        UCHAR			iDevice,        // 低7位指定I2C设备地址
        UCHAR			iAddr,          // 指定数据单元的地址
        PUCHAR			oByte );        // 指向一个字节单元,用于保存读取的字节数据
    BOOL    writeI2C(                   // 向I2C接口写入一个字节数据
        UCHAR			iDevice,        // 低7位指定I2C设备地址
        UCHAR			iAddr,          // 指定数据单元的地址
        UCHAR			iByte );        // 待写入的字节数据
    BOOL    readI2CEx(                  // 从I2C接口读取多字节数据
        UCHAR			iDevice,        // 低7位指定I2C设备地址
        UCHAR			iAddr,          // 指定数据单元的地址
        PULONG			iLength,        // 数据块长度
        PUCHAR			iBuf );         // 指向一个字节单元,用于保存读取的字节数据
    BOOL    writeI2CEx(                 // 向I2C接口写入一个字节数据
        UCHAR			iDevice,        // 低7位指定I2C设备地址
        UCHAR			iAddr,          // 指定数据单元的地址
        PULONG			oLength,        // 数据块长度
        PUCHAR			oBuf );         // 待写入的字节数据

    BOOL    readIoByte(                 // 从I/O端口读取一个字节
        UCHAR			iAddr,          // 指定I/O端口的地址
        PUCHAR			oByte );        // 指向一个字节单元,用于保存读取的字节数据
    BOOL    writeIoByte(                // 向I/O端口写入一个字节
        UCHAR			iAddr,          // 指定I/O端口的地址
        UCHAR			iByte );        // 待写入的字节数据


private:
    VOID            openInit();
    mPCH367_IO_REG  ioReg;
    BOOL            openFlag;
//    BOOL            readyFlag;
    HANDLE          handle;

};



#endif // CH367_H
