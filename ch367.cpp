#include "ch367.h"
#include <qdebug.h>


//i2C addition
BOOL    WINAPI  CH367ReadI2CEx(     // 从I2C接口读取多字节数据
    UCHAR			iDevice,        // 低7位指定I2C设备地址
    UCHAR			iAddr,          // 指定数据单元的地址
    PULONG			iLength,        // 数据块长度
    PUCHAR			iBuf );         // 指向一个字节单元,用于保存读取的字节数据

BOOL    WINAPI  CH367WriteI2CEx(   // 向I2C接口写入一个字节数据
    UCHAR			iDevice,       // 低7位指定I2C设备地址
    UCHAR			iAddr,         // 指定数据单元的地址
    PULONG			oLength,       // 数据块长度
    PUCHAR			oBuf );        // 待写入的字节数据


CH367::CH367()
    :openFlag(false)
    ,handle(INVALID_HANDLE_VALUE){
    memset(&ioReg, 0, sizeof(mPCH367_IO_REG));
}

CH367::~CH367(){
//    handle = INVALID_HANDLE_VALUE;
    closeDevice();
}

BOOL CH367::openDevice(){
    handle = CH367OpenDevice(false, false, 0);
    if(handle == INVALID_HANDLE_VALUE){
        qDebug() << "open ch367 failed!";
        return false;
    }
    qDebug() << "open ch367 succued " << handle;
    openInit();
    openFlag = true;
    return true;
}

void CH367::closeDevice(){
    if(openFlag){
        CH367CloseDevice();
        openFlag = false;
    }
    qDebug() << "close ch367";
}

BOOL CH367::isOpen(){
    qDebug() << "ch367 open flag is" << openFlag;
    return openFlag;
}

//BOOL    isready();

HANDLE  CH367::getHandle(){
    return handle;
}

VOID CH367::openInit(){
    if(CH367GetIoBaseAddr(&ioReg))
    {
        qDebug() << "ch367 openInit success";
    }
}

BOOL CH367::readI2C(UCHAR iDevice, UCHAR iAddr, PUCHAR oByte){
    return CH367ReadI2C(iDevice, iAddr, oByte);
}

BOOL CH367::writeI2C(UCHAR iDevice, UCHAR iAddr, UCHAR iByte){
    return CH367WriteI2C(iDevice, iAddr, iByte);
}

BOOL CH367::readI2CEx(UCHAR iDevice, UCHAR iAddr, PULONG iLength, PUCHAR iBuf){
//    qDebug() << iDevice << " " << iAddr << " " << iLength << " " << iBuf;
    bool i = CH367ReadI2CEx(iDevice, iAddr, iLength, iBuf);
//    qDebug() << "readI2CEx hyyyy" << i;
    return i;
}

BOOL CH367::writeI2CEx(UCHAR iDevice, UCHAR iAddr, PULONG oLength, PUCHAR oBuf){
    return CH367WriteI2CEx(iDevice, iAddr, oLength, oBuf);
}

BOOL CH367::readIoByte(UCHAR iAddr, PUCHAR oByte){
    return CH367ReadIoByte(&ioReg->mCH367IoPort[iAddr], oByte);
}

BOOL CH367::writeIoByte(UCHAR iAddr, UCHAR iByte){
    return CH367WriteIoByte(&ioReg->mCH367IoPort[iAddr], iByte);
}





/*I2C操作*/
//用宏替换简化对SDA和SCL的置高置低
#define CH367_SDA_SET                        \
{                                                           \
   CH367ReadIoByte((PVOID)0xE8,&Regval);            \
   CH367WriteIoByte((PVOID)0xE8,(UCHAR)(Regval|1)); \
}
#define CH367_SDA_CLR                        \
{                                                           \
   CH367ReadIoByte((PVOID)0xE8,&Regval);            \
   CH367WriteIoByte((PVOID)0xE8,(UCHAR)(Regval&0xFE)); \
}
#define CH367_SCL_SET                           \
{                                                              \
   CH367ReadIoByte((PVOID)0xE8,&Regval);               \
   CH367WriteIoByte((PVOID)0xE8,(UCHAR)(Regval|0x02)); \
}
#define CH367_SCL_CLR                           \
{                                                              \
   CH367ReadIoByte((PVOID)0xE8,&Regval);               \
   CH367WriteIoByte((PVOID)0xE8,(UCHAR)(Regval&0xFD)); \
}

#define DELAY1 DelayTime1(1)
#define DELAY2 DelayTime1(2)

//延时函数,以us为单位
VOID DelayTime1(double TimerVal){//定时值为ms,其定时误差一般不超过0.5微秒，精度与CPU等机器配置有关
    LARGE_INTEGER litmp;
    LONGLONG QPart1,QPart2;
    double dfMinus, dfFreq, dfTim,NewTimerVal;
    NewTimerVal = TimerVal*0.001*0.001;       //将ms定时值转成s值
    QueryPerformanceFrequency(&litmp);  //频率以HZ为单位
    dfFreq = (double)litmp.QuadPart;    //获得计数器的时钟频率
    QueryPerformanceCounter(&litmp);
    QPart1 = litmp.QuadPart;            //获得初始值
    do{
        QueryPerformanceCounter(&litmp);
        QPart2 = litmp.QuadPart;        //获得中止值
        dfMinus = (double)(QPart2-QPart1);
        dfTim = dfMinus / dfFreq;       //获得对应的时间值=振荡次数/振荡频率，单位为秒
    }while(dfTim<NewTimerVal);
    return;
}

BOOL WINAPI CH367ReadI2CEx(  	// 从I2C接口读取多字节数据
    UCHAR			iDevice,  	// 低7位指定I2C设备地址
    UCHAR			iAddr,  	// 指定数据单元的地址
    PULONG			iLength,  	// 数据块长度
    PUCHAR			iBuf )  	// 指向一个字节单元,用于保存读取的字节数据
{
    ULONG i=0,NumB;
    UCHAR Regval,iAck;

    NumB = *iLength;
    *iLength = 0;
    // 启动IIC总线:时钟SCL线为高电平时，数据线SDA出现由高电平向低电平变化时
    {
        CH367_SDA_SET  // SDA置高电平
        CH367_SCL_SET  // SCL置高电平
        DELAY2;
        CH367_SDA_CLR   // SDA置低电平
        DELAY2;
        CH367_SCL_CLR   // SCL置低电平
    }

    // 发送从器件的设备地址和写命令
    {// 移位发送的数据,高位在前
        UCHAR bit,RollByte = 0;

        RollByte = (iDevice<<1)&0xFE; //取低七位作为设备地址,最低为0写命令
        for(bit=0;bit<8;bit++)
        {
            if(RollByte&0x80) CH367_SDA_SET // 位1则输出高电平
            else CH367_SDA_CLR           // 位0则输出高电平
            CH367_SCL_SET;               // 生成一个时钟脉冲,让从器件读取数据
            DELAY1;
            CH367_SCL_CLR;
            RollByte <<= 1;
        }
    }
    // 生成第九个时钟脉冲,接收从器件的应答
    {
        CH367_SCL_SET // 生成第九个时钟
        //读应答位
        CH367ReadIoByte((PVOID)0xEA,&Regval);
        iAck = Regval&0x01; // SDA为高电平,为非应答信号
        CH367_SCL_CLR       // 清时钟线SCL
        if( iAck )// 为非应答信号,设备无响应则返回
            goto ExitRdI2CEx;
    }
    // 输出I2C操作的单元地址
    {// 移位准备发送的数据,高位在前
        UCHAR bit,RollByte = 0;

        RollByte = iAddr;
        for(bit=0;bit<8;bit++)
        {
            if(RollByte&0x80) CH367_SDA_SET // 位1则输出高电平
            else CH367_SDA_CLR              // 位0则输出高电平
            CH367_SCL_SET;                  // 生成一个时钟脉冲,让从器件读取数据
            DELAY1;
            CH367_SCL_CLR;
            RollByte <<= 1;
        }
    }
    {// 生成第九个时钟脉冲,接收从器件的应答
        CH367_SDA_SET
        CH367_SCL_SET
        iAck = 0;
        //读应答位
        CH367ReadIoByte((PVOID)0xEA,&Regval);
        iAck = Regval&0x01; // SDA为高电平,为非应答信号
        CH367_SCL_CLR       // 清时钟线SCL
        if( iAck )// 为非应答信号,设备无响应则返回
            goto ExitRdI2CEx;
    }
    // 重新启动IIC总线:时钟SCL线为高电平时，数据线SDA出现由高电平向低电平变化时
    {
        CH367_SDA_SET  // SDA置高电平
        CH367_SCL_SET  // SCL置高电平
        DELAY2;
        CH367_SDA_CLR   // SDA置低电平
        DELAY2;
        CH367_SCL_CLR   // SCL置低电平
    }

    // 发送从器件的7位设备地址和读命令
    {// 移位发送数据,高位在前
        UCHAR bit,RollByte = 0;

        RollByte = (iDevice<<1)|0x01; // 取低七位作为设备地址,最低为1读命令
        for(bit=0;bit<8;bit++)
        {
            if(RollByte&0x80) CH367_SDA_SET // 位1则输出高电平
            else CH367_SDA_CLR           // 位0则输出高电平
            CH367_SCL_SET;               // 生成一个时钟脉冲,让从器件读取数据
            DELAY1;
            CH367_SCL_CLR;
            RollByte <<= 1;
        }
    }
    {// 生成第九个时钟脉冲,接收从器件的应答
        CH367_SDA_SET
        CH367_SCL_SET
        //读应答位
        CH367ReadIoByte((PVOID)0xEA,&Regval);
        iAck = Regval&0x01; // SDA为高电平,为非应答信号
        CH367_SCL_CLR       // 清时钟线SCL
        if( iAck )// 为非应答信号,设备无响应则返回
            goto ExitRdI2CEx;
    }
    // 从SDA线上接收8位字节数据
    for(i=0;i<NumB;i++)
    {
        {// 移位发送数据,高位在前
            UCHAR RollByte = 0,bit;
            CH367_SDA_SET
            for(bit=0;bit<8;bit++)
            {
                RollByte <<= 1;
                CH367_SCL_SET // 生成时钟信号,输出位
                DELAY1;
                CH367ReadIoByte((PVOID)0xEA,&Regval); // 在SCL=1期间从SDA内读入数据位
                if(Regval&0x01)	RollByte++;
                CH367_SCL_CLR
            }
            iBuf[i] = RollByte;
        }
        // 读完8位字节后设置应答
        if( i == (NumB-1) ) // 已接收完最后一个数据,设置非应答信号,通知结束
        {
            CH367_SDA_SET     // SDA置高电平
            CH367_SCL_SET     // SCL置高电平
            DELAY1;
            CH367_SCL_CLR     // SCL置低电平
            CH367_SDA_CLR     // SDA置低电平
        }
        else // 不是最后一个数据则应答,通知继续
        {
            CH367_SDA_CLR    // SDA线置低电平
            CH367_SCL_SET    // SCL线置高电平
            DELAY1;
            CH367_SCL_CLR    // SCL线置低电平
            CH367_SDA_SET    // SDA线置高电平
        }
    }
    *iLength = i; // 置已读取数据长度
    // 发送I2C停止位:时钟SCL线为高电平时,数据线SDA出现由低到高的电平变换
    {
        CH367_SDA_CLR  // 置数据线,时钟线高电平时数据线正跳变
        CH367_SCL_SET
        DELAY1;
        CH367_SDA_SET
        DELAY1;
        CH367_SDA_CLR  // 清SDA线
        CH367_SCL_CLR  // 清SCL线
    }
ExitRdI2CEx:
    return iAck?FALSE:TRUE;
}

BOOL	WINAPI	CH367WriteI2CEx(  	// 向I2C接口写入一个字节数据
    UCHAR			iDevice,       	// 低7位指定I2C设备地址
    UCHAR			iAddr,         	// 指定数据单元的地址
    PULONG			oLength,       	// 数据块长度
    PUCHAR			oBuf )        	// 待写入的字节数据
{
    ULONG i=0,NumB;
    UCHAR Regval,iAck;

    NumB = *oLength;

    // 启动IIC总线:时钟SCL线为高电平时，数据线SDA出现由高电平向低电平变化时
    {
        CH367_SDA_SET  // SDA置高电平
        CH367_SCL_SET  // SCL置高电平
        DELAY2;
        CH367_SDA_CLR   // SDA置低电平
        DELAY2;
        CH367_SCL_CLR   // SCL置低电平
    }

    // 发送从器件的设备地址和写命令
    {// 移位发送的数据,高位在前
        UCHAR bit,RollByte = 0;

        RollByte = (iDevice<<1)&0xFE; //取低七位作为设备地址,最低为0写命令
        for(bit=0;bit<8;bit++)
        {
            if(RollByte&0x80) CH367_SDA_SET // 位1则输出高电平
            else CH367_SDA_CLR           // 位0则输出高电平
            CH367_SCL_SET;               // 生成一个时钟脉冲,让从器件读取数据
            DELAY1;
            CH367_SCL_CLR;
            RollByte <<= 1;
        }
    }
    // 生成第九个时钟脉冲,接收从器件的应答
    {
        //CH367_SDA_SET //在读取SDA值前是否需要将此引脚拉高??
        CH367_SCL_SET // 生成第九个时钟
        //读应答位
        CH367ReadIoByte((PVOID)0xEA,&Regval);
        iAck = Regval&0x01; // SDA为高电平,为非应答信号
        CH367_SCL_CLR       // 清时钟线SCL
        if( iAck )// 为非应答信号,设备无响应则返回
            goto ExitWrI2CEx;
    }
    // 输出I2C操作的单元地址
    {// 移位准备发送的数据,高位在前
        UCHAR bit,RollByte = 0;

        RollByte = iAddr;
        for(bit=0;bit<8;bit++)
        {
            if(RollByte&0x80) CH367_SDA_SET // 位1则输出高电平
            else CH367_SDA_CLR              // 位0则输出高电平
            CH367_SCL_SET;                  // 生成一个时钟脉冲,让从器件读取数据
            DELAY1;
            CH367_SCL_CLR;
            RollByte <<= 1;
        }
    }
    {// 生成第九个时钟脉冲,接收从器件的应答
        CH367_SDA_SET
        CH367_SCL_SET
        iAck = 0;
        //读应答位
        CH367ReadIoByte((PVOID)0xEA,&Regval);
        iAck = Regval&0x01; // SDA为高电平,为非应答信号
        CH367_SCL_CLR       // 清时钟线SCL
        if( iAck )// 为非应答信号,设备无响应则返回
            goto ExitWrI2CEx;
    }
    // 向SDA线上发送8位字节数据
    for(i=0;i<NumB;i++)
    {
        {// 移位发送数据,高位在前
            UCHAR RollByte = 0,bit;

            RollByte = oBuf[i];
            for(bit=0;bit<8;bit++)
            {
                if(RollByte&0x80) CH367_SDA_SET // 位1则输出高电平
                else CH367_SDA_CLR           // 位0则输出高电平
                CH367_SCL_SET;               // 生成一个时钟脉冲,让从器件读取数据
                DELAY1;
                CH367_SCL_CLR;
                RollByte <<= 1;
            }
        }
        {// 生成第九个时钟脉冲,接收从器件的应答
            //CH367_SDA_SET //在读取SDA值前是否需要将此引脚拉高??
            CH367_SCL_SET // 生成第九个时钟
            //读应答位
            CH367ReadIoByte((PVOID)0xEA,&Regval);
            iAck = Regval&0x01; // SDA为高电平,为非应答信号
            CH367_SCL_CLR       // 清时钟线SCL
            if( iAck )// 为非应答信号,设备无响应则返回
            {
                *oLength = i;
                goto ExitWrI2CEx;
            }
        }
    }
    *oLength = i;

    // 发送I2C停止位:时钟SCL线为高电平时,数据线SDA出现由低到高的电平变换
    {
        CH367_SDA_CLR  // 置数据线,时钟线高电平时数据线正跳变
        CH367_SCL_SET
        DELAY1;
        CH367_SDA_SET
        DELAY1;
        CH367_SDA_CLR  // 清SDA线
        CH367_SCL_CLR  // 清SCL线
    }
ExitWrI2CEx:
        return iAck?FALSE:TRUE;
}
