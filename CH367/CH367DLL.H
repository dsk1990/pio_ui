// 2011.07.01 V1.0
//****************************************
//**  Copyright  (C)  W.ch  1999-2011   **
//**  Web:  http://www.winchiphead.com  **
//****************************************
//**  DLL for PCI interface chip CH367/8**
//**  C, VC5.0                          **
//****************************************
//
// PCIe总线接口芯片CH367的应用层接口库 V1.0
// 南京沁恒电子有限公司 作者: TECH30 2011.07
// CH367-DLL  V1.0 ,    Support: IO/MEM/INT
// 运行环境: Windows 98/ME, Windows 2000/XP/7
//
/* !!注意点:
     1.CH367DLL接口适应于CH367&CH368芯片,CH367开头的函数适用于CH367及CH368,CH368开头的函数只适用于CH368芯片,不适用于CH367.   
     2.CH368支持PC机程序以四字节（双字）为单位对I/O 端口或者存储器进行读写。
       CH367mReadIoWord/CH367mWriteIoWord，进行字操作时，起始地址必须是基址范围内的任意字边界的地址（2 的倍数）；
       CH367mReadIoDword/CH367mWriteIoDword/CH368ReadMemDword/CH368WriteMemDword进行四字节存取时，起始地址必须是基址范围内的任意双字边界的地址（4 的倍数）
*/

#ifndef		_CH367_DLL_H
#define		_CH367_DLL_H


//dsk addition
#ifdef _WIN32
#include <Windows.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif


#define		mOFFSET( s, m )			( (ULONG_PTR) & ( ( ( s * ) 0 ) -> m ) )	// 定义获取结构成员相对偏移地址的宏

#ifndef		max
#define		max( a, b )				( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )	// 较大值
#endif

#ifndef		min
#define		min( a, b )				( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )	// 较小值
#endif

#ifdef		ExAllocatePool
#undef		ExAllocatePool						// 删除带TAG的内存分配
#endif

#ifndef		NTSTATUS
typedef		LONG	NTSTATUS;					// 返回状态
#endif


typedef	struct	_PCI_CONFIG {					// 定义PCI配置空间数据结构
	USHORT			mPcVendorId;				// 00H 供应商标识
	USHORT			mPcDeviceId;				// 02H 设备标识
	USHORT			mPcCommandReg;				// 04H 命令寄存器
	USHORT			mPcStatusReg;				// 06H 状态寄存器
	UCHAR			mPcRevisionId;				// 08H 修改标识
	UCHAR			mPcProgramIf;				// 09H 寄存器级编程接口
	UCHAR			mPcSubClass;				// 0AH 子类代码
	UCHAR			mPcBaseClass;				// 0BH 基本分类代码
	UCHAR			mPcCacheLine;				// 0CH 缓存行长度
	UCHAR			mPcLatenTimer;				// 0DH 延迟计数器
	UCHAR			mPcHeaderType;				// 0EH 头标类型
	UCHAR			mPcBistReg;					// 0FH 内含自测试寄存器
	ULONG			mPcBaseAddr0;				// 10H 基址寄存器0
	ULONG			mPcBaseAddr1;				// 14H 基址寄存器1
	ULONG			mPcBaseAddr2;				// 18H 基址寄存器2
	ULONG			mPcBaseAddr3;				// 1CH 基址寄存器3
	ULONG			mPcBaseAddr4;				// 20H 基址寄存器4
	ULONG			mPcBaseAddr5;				// 24H 基址寄存器5
	ULONG			mPcCardCis;					// 28H
	USHORT			mPcSubSysVen;				// 2CH 子系统供应商标识
	USHORT			mPcSubSysDev;				// 2EH 子系统设备标识
	ULONG			mPcExpansRom;				// 30H 扩展ROM基址寄存器
	UCHAR			mPcCapPtr;					// 34H
	UCHAR			mPcReserved1[3];			// 35H
	ULONG			mPcReserved2;				// 38H
	UCHAR			mPcInterLine;				// 3CH 中断线寄存器
	UCHAR			mPcInterPin;				// 3DH 中断引脚寄存器
	UCHAR			mPcMinGrant;				// 3EH
	UCHAR			mPcMaxLatency;				// 3FH
} mPCI_CONFIG, *mPPCI_CONFIG;

typedef	struct	_PCI_EXP_ROM {					// PCI扩展ROM的数据结构
	UCHAR			mPerRomSig[4];				// 00H PCI扩展ROM签名字符串'PCIR'
	USHORT			mPerVendorId;				// 04H 供应商标识
	USHORT			mPerDeviceId;				// 06H 设备标识
	USHORT			mPerVpdPtr;					// 08H 重要产品数据指针
	USHORT			mPerStrucLen;				// 0AH PCI扩展ROM数据结构的长度
	UCHAR			mPerRevision;				// 0CH PCI扩展ROM数据结构的修改版本
	UCHAR			mPerProgramIf;				// 0DH 寄存器级编程接口
	UCHAR			mPerSubClass;				// 0EH 子类代码
	UCHAR			mPerBaseClass;				// 0FH 基本分类代码
	USHORT			mPerImageLen;				// 10H 映像长度
	USHORT			mPerImageRev;				// 12H 映像中代码/数据的修改版本
	UCHAR			mPerCodeType;				// 14H 代码类型
	UCHAR			mPerIndicator;				// 15H 映像指示标志
	USHORT			mPerReserved;				// 16H
} mPCI_EXP_ROM, *mPPCI_EXP_ROM;

typedef	struct	_CH367_IO_REG {	                //CH367芯片的I/O空间寄存器
	UCHAR mCH367IoPort[0xE8];                     //00H-E7H,共232字节为标准的I/O端口
	UCHAR mCH367GPOR;	                        //E8H 通用输出寄存器
	UCHAR mCH367GPVR;	                        //E9H 通用变量寄存器
	UCHAR mCH367GPIR;	                        //EAH 通用输入寄存器
	UCHAR mCH367IntCtr;	                        //EBH 中断控制寄存器
	union{
		UCHAR mCH367IoBuf8;                     //ECH 8位被动并行接口数据缓冲区
		ULONG mCH367IoBuf32;                    //ECH 32位被动并行接口数据缓冲区
	};
	union{
		USHORT mCH368MemAddr;                   //F0H 存储器接口: A15-A0地址设定寄存器 ??
		struct{
			UCHAR mCH368MemAddrL;               //F0H 存储器接口: A7-A0地址设定寄存器
			union{
				UCHAR mCH368MemAddrH;           //F1H 存储器接口: A15-A8地址设定寄存器
				UCHAR mCH367GPOR2;              //F1H 通用输出寄存器2 ??
			};
		}ASR;
	};
	UCHAR mCH367IORESV2;                        //F2H
	UCHAR mCH368MemData;                        //F3H 存储器接口: 存储器数据存取寄存器
	union{
		UCHAR mCH367Data8Sta;                   //F4H D7-D0端口状态寄存器
		ULONG mCH367SData32Sta;                 //F4H D31-D0端口状态寄存器
	};
	UCHAR mCH367Status;                         //F8H 杂项控制和状态寄存器
	UCHAR mCH367IO_RESV3;                       //F9H
	UCHAR mCH367Speed;                          //FAH 读写速度控制寄存器
	UCHAR mCH367PDataCtrl;                      //FBH 被动并行接口控制寄存器
	UCHAR mCH367IoTime;                         //FCH 硬件循环计数寄存器
	UCHAR mCH367SPICtrl;                        //FDH SPI控制寄存器
	UCHAR mCH367SPIData;                        //FEH SPI数据寄存器
	UCHAR mCH367IO_RESV4;                       //FFH
} mCH367_IO_REG, *mPCH367_IO_REG;

typedef	struct	_CH368_MEM_REG {				// CH367芯片的存储器空间
	UCHAR			mCH368MemPort[0x8000];		// 0000H-7FFFH,共32768字节为标准的存储器单元
} mCH368_MEM_REG, *mPCH368_MEM_REG;

typedef	struct	_WIN32_COMMAND {				// 定义WIN32命令接口结构
	union	{
		ULONG		mFunction;					// 输入时指定功能代码
		NTSTATUS	mStatus;					// 输出时返回操作状态
	};
	ULONG			mLength;					// 存取长度,返回后续数据的长度
	union	{
		PVOID			mAddress;				// 起始地址,返回地址
		ULONGLONG		mAddress64;				// 起始地址,返回地址
	};
	UCHAR			mBuffer[8];					// 数据缓冲区,长度为0至32KB
} mWIN32_COMMAND, *mPWIN32_COMMAND;

// WIN32应用层接口命令
#define		IOCTL_CH367_COMMAND		( FILE_DEVICE_UNKNOWN << 16 | FILE_ANY_ACCESS << 14 | 0x0f36 << 2 | METHOD_BUFFERED )	// 专用接口

#define		mWIN32_COMMAND_HEAD		mOFFSET( mWIN32_COMMAND, mBuffer )	// WIN32命令接口的头长度

#define		mCH367_MAX_NUMBER		16			// 最多同时连接的CH367数

#define		mMAX_BUFFER_LENGTH		max( sizeof( mCH367_IO_REG ), sizeof( mCH368_MEM_REG ) )	// 数据缓冲区最大长度

#define		mMAX_COMMAND_LENGTH		( mWIN32_COMMAND_HEAD + mMAX_BUFFER_LENGTH )	// 最大数据长度加上命令结构头的长度

#define		mCH368_MEM_BASE_AUTO	( (PVOID)(ULONG_PTR)0xffffffff )	// 自动设定CH368的存储器基址

#define		mCH367_INT_LINE_AUTO	0xffffffff				// 自动检测CH367的中断号

// 寄存器的位定义
//0xE8
#define		mBitI2cSdaOut           0x01        //设定SDA 引脚的输出值(1),1*:high,0:low
#define		mBitI2cSclOut           0x02        //设定SCL 引脚的输出值(1)
#define		mBitSpiScsOut           0x04        //设定SCS 引脚的输出值(1)
#define		mBitBeWakenEnable       0x32        //使能支持被强制唤醒(0)
#define		mBitSetSpiSdxDir        0x64        //设定SDX 引脚的数据方向(0)
//0xEA
#define		mBitSpiSdxOut           0x01        //输入SDA 引脚的状态(1)
#define		mBitIntStatus           0x08        //输入INT#引脚的状态(1)
#define		mBitRDStatus            0x10        //输入RD#引脚的状态(1)
#define		mBitWRStatus            0x20        //输入WR#引脚的状态(1)
#define		mBitAddrStatus          0x40        //输入ADDR 引脚的状态(1)
#define		mBitSdxStatus           0x80        //输入SDX 引脚的状态(1)
//0xEB
#define		mBitGlobalIntEnable     0x02        //全局中断使能(0)
#define		mBitIntPolarity         0x04        //INT#引脚中断输入的极性(0),0:低电平/上升沿;1:高电平/下降沿
#define		mBitIntInType           0x08        //INT#引脚中断输入的类型(0)
//0xF8:
#define		mBitAddr15Out           0x01        //设定A15 引脚的输出值(1)
#define		mBitIntAction           0x04        //中断激活状态(0)
#define		mBitIntStatus           0x08        //输入INT#引脚的状态(1)     
#define		mBitRST0Out             0x80        //设定RSTO 引脚的输出值(1)
//0xFA
#define		mBitSpeedInact          0xFA        //含建立时间和保持时间的读写信号总宽度(0111)
#define		mBitDataAddrOutCreate   0x10        //数据和地址输出建立时间(0),0:15nS,1:45nS
#define		mBitDataAddrOutKeep     0x20        //数据和地址输出保持时间(0),0:15nS,1:45nS
#define		mBitLocalBusWidth       0x40        //本地数据总线宽度(0),0:8位,1:32位
//0xFD
#define		mBitHWCountH4           0x0F        //硬件循环计数的高4 位(XXXX),与硬件循环计数寄存器CNTR 合在一起共12 位
#define		mBitSpiTransportStatus  0x10        //SPI 传输正在进行状态(0),0:空闲,1:正在传输
#define		mBitSpiClockFreq        0x20        //选择SPI 串行时钟频率(0),0:31.3MHz,1:15.6MHz
#define		mBitSelSpiInPin         0x40        //选择SPI 数据输入引脚(0),0:SDK,1:ADDR
#define		mBitStartNewSPITrans    0x80        //使能读SPIDR 后启动新传输(0),0:读后空闲,1:读后启动


// 应用层接口的功能代码
#define		mFuncNoOperation		0x00000000	// 无操作
#define		mFuncGetVersion			0x00000001	// 获取驱动程序版本号
#define		mFuncGetIoBaseAddr		0x00000004	// 读取I/O端口基址
#define		mFuncSetIoBaseAddr		0x00000005	// 设置I/O端口基址
#define		mFuncGetMemBaseAddr		0x00000006	// 读取存储器基址
#define		mFuncSetMemBaseAddr		0x00000007	// 设置存储器基址,自动设定存储器基址
#define		mFuncGetInterLine		0x00000008	// 读取中断号
#define		mFuncSetInterLine		0x00000009	// 设置中断号,自动检测中断号
#define		mFuncWaitInterrupt		0x0000000a	// 等待中断,直到CH367产生中断
#define		mFuncAbortWaitInter		0x0000000b	// 放弃等待中断,终止等待
#define		mFuncSetExclusive		0x0000000c	// 设置独占使用
#define		mFuncReadIoByte			0x00000010	// 读取输入输出端口,在同一个端口地址以字节为单位连续读取
#define		mFuncReadIoWord			0x00000011	// 读取输入输出端口,在同一个端口地址以字为单位连续读取
#define		mFuncReadIoDword		0x00000012	// 读取输入输出端口,在同一个端口地址以双字为单位连续读取
#define		mFuncReadIoBlock		0x00000013	// 读取输入输出端口,每读取一个字节,端口地址加一
#define		mFuncReadIo32Block		0x00000028	// 读取输入输出端口,每读取四字节,端口地址加四,最大长度232B(从偏移地址00H读到E7H)
#define		mFuncWriteIoByte		0x00000014	// 写入输入输出端口,在同一个端口地址以字节为单位连续写入
#define		mFuncWriteIoWord		0x00000015	// 写入输入输出端口,在同一个端口地址以字为单位连续写入
#define		mFuncWriteIoDword		0x00000016	// 写入输入输出端口,在同一个端口地址以双字为单位连续写入
#define		mFuncWriteIoBlock		0x00000017	// 写入输入输出端口,每写入一个字节,端口地址加一
#define		mFuncWriteIo32Block		0x00000029	// 写入输入输出端口,每写入一个四字节,端口地址加四,最大长度232B(从偏移地址00H写到E7H)
#define		mFuncReadMemByte		0x00000018	// 读取存储器/寄存器
#define		mFuncReadMemDword		0x0000001a	// 读取存储器/寄存器
#define		mFuncWriteMemByte		0x0000001c	// 写入存储器/寄存器
#define		mFuncWriteMemDword		0x0000001e	// 写入存储器/寄存器
#define		mFuncReadConfig			0x00000020	// 读取PCI配置空间
#define		mFuncWriteConfig		0x00000021	// 写入PCI配置空间
#define		mFuncReadBuffer1		0x00000024	// 读取中断命令缓冲区1
#define		mFuncWriteBuffer1		0x00000025	// 写入中断命令缓冲区1
#define		mFuncReadBuffer2		0x00000026	// 读取中断命令缓冲区2
#define		mFuncWriteBuffer2		0x00000027	// 写入中断命令缓冲区2

#define		mFuncStreamSPI	    	0x0000002A	// SPI数据流传输函数
#define		mFuncSetStreamMode    	0x0000002B	// 设置SPI为SPI3或SPI4
#define		mFuncSetInterMode    	0x0000002C	// 设置中断极性及输入类型


#define		mFuncFlashLock    	0x0000002D	// 对Flash-ROM存储器进行写保护设定 
#define		mFuncFlashRead    	0x0000002E	// 从Flash-ROM存储器读取数据块
#define		mFuncFlashErase    	0x0000002F	// 对Flash-ROM存储器的指定区域进行擦除,每4096字节即4K为一个扇区,最小擦除单位是扇区
#define		mFuncFlashWrite    	0x00000030	// 向Flash-ROM存储器写入数据块

typedef		VOID	( CALLBACK	* mPCH367_INT_ROUTINE ) ( VOID );		// 中断服务程序



HANDLE	WINAPI	CH367OpenDevice(  // 打开CH367设备,返回句柄,出错则无效
	BOOL			iEnableMemory,  // 是否需要支持存储器,CH367芯片不支持,CH368芯片支持
	BOOL			iEnableInterrupt,  // 是否需要支持中断
    UCHAR           iInterruptMode ); // 位0:中断输入的极性1:高电平/下降沿;0:低电平/上升沿;位1:中断输入的类型 1:边沿,0:电平


VOID	WINAPI	CH367CloseDevice( );  // 关闭CH367设备


ULONG	WINAPI	CH367GetVersion( );  // 获得DLL版本号,返回版本号


ULONG	WINAPI	CH367DriverCommand(  // 直接传递命令给驱动程序,出错则返回0,否则返回数据长度
	mPWIN32_COMMAND	ioCommand );  // 命令结构的指针
// 该程序在调用后返回数据长度,并且仍然返回命令结构,如果是读操作,则数据返回在命令结构中,
// 返回的数据长度在操作失败时为0,操作成功时为整个命令结构的长度,例如读一个字节,则返回mWIN32_COMMAND_HEAD+1,
// 命令结构在调用前,分别提供:命令功能代码,起始地址(可选),存取数据的长度(可选),
// 命令结构在调用后,分别返回:操作状态代码,返回的基址(可选),后续数据的长度(可选),
// 操作状态代码是由WINDOWS定义的代码,可以参考NTSTATUS.H,
// 返回的基址只适用于下列命令:获取I/O基址,获取存储器基址,获取中断号,对于其它命令则保持输入时的起始地址
// 后续数据的长度是指读操作返回的数据长度,数据存放在随后的缓冲区中,对于写操作一般为0

ULONG	WINAPI	CH367GetDrvVersion( );  // 获得驱动程序版本号,返回版本号,出错则返回0


BOOL	WINAPI	CH367GetIoBaseAddr(  // 获取I/O端口的基址
	mPCH367_IO_REG	*oIoBaseAddr );  // 保存I/O端口基址的单元地址


BOOL	WINAPI	CH367SetIoBaseAddr(  // 设定I/O端口的基址
	mPCH367_IO_REG	iIoBaseAddr );  // 指定I/O端口基址


BOOL	WINAPI	CH368GetMemBaseAddr(  // 获取存储器的基址
	mPCH368_MEM_REG	*oMemBaseAddr );  // 保存存储器基址的单元地址


BOOL	WINAPI	CH368SetMemBaseAddr(  // 设定存储器的基址
	mPCH368_MEM_REG	iMemBaseAddr );  // 指定存储器基址,为0则关闭存储器,为-1则自动设定


BOOL	WINAPI	CH367GetIntLine(  // 获取中断号
	PULONG			oIntLine );  // 保存中断号的单元地址


BOOL	WINAPI	CH367SetIntLine(  // 设定中断号
	ULONG			iIntLine,  // 指定中断号,为0则关闭中断,为-1则自动检测并设定
	UCHAR           iInterruptMode ); // 位0:中断输入的极性1:高电平下降沿;0:低电平上升沿;位1:中断输入的类 1:边沿,0:中断


BOOL	WINAPI	CH367WaitInterrupt( );  // 等待中断事件


BOOL	WINAPI	CH367AbortWaitInt( );  // 放弃等待中断


BOOL	WINAPI	CH367SetIntRoutine(  // 设定中断服务程序
	mPCH367_INT_ROUTINE	iIntRoutine );  // 指定中断服务程序,为NULL则取消中断服务,否则在中断时调用该程序


BOOL	WINAPI	CH367ReadIntCommand(  // 读取中断命令缓冲区
	mPWIN32_COMMAND	oCommand,  // 指向一个足够大的缓冲区,用于保存读取的命令结构
	ULONG			iCmdIndex );  // 中断命令序号,为1或者2


BOOL	WINAPI	CH367WriteIntCommand(  // 写入中断命令缓冲区
	mPWIN32_COMMAND	iCommand,  // 指向作为中断命令的命令结构
	ULONG			iCmdIndex );  // 中断命令序号,为1或者2


BOOL	WINAPI	CH367ReadIoByte(  // 从I/O端口读取一个字节
	PVOID			iAddr,  // 指定I/O端口的地址
	PUCHAR			oByte );  // 指向一个字节单元,用于保存读取的字节数据


BOOL	WINAPI	CH367ReadIoWord(  // 从I/O端口读取一个字
	PVOID			iAddr,  // 指定I/O端口的地址
	PUSHORT			oWord );  // 指向一个字单元,用于保存读取的字数据


BOOL	WINAPI	CH367ReadIoDword(  // 从I/O端口读取一个双字
	PVOID			iAddr,  // 指定I/O端口的地址
	PULONG			oDword );  // 指向一个双字单元,用于保存读取的双字数据


BOOL	WINAPI	CH367WriteIoByte(  // 向I/O端口写入一个字节
	PVOID			iAddr,  // 指定I/O端口的地址
	UCHAR			iByte );  // 待写入的字节数据


BOOL	WINAPI	CH367WriteIoWord(  // 向I/O端口写入一个字
	PVOID			iAddr,  // 指定I/O端口的地址
	USHORT			iWord );  // 待写入的字数据


BOOL	WINAPI	CH367WriteIoDword(  // 向I/O端口写入一个双字
	PVOID			iAddr,  // 指定I/O端口的地址
	ULONG			iDword );  // 待写入的双字数据


BOOL	WINAPI	CH368ReadMemByte(  // 从存储器读取一个字节
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	PUCHAR			oByte );  // 指向一个字节单元,用于保存读取的字节数据


BOOL	WINAPI	CH368ReadMemDword(  // 从存储器读取一个双字
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	PULONG			oDword );  // 指向一个双字单元,用于保存读取的双字数据


BOOL	WINAPI	CH368WriteMemByte(  // 向存储器写入一个字节
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	UCHAR			iByte );  // 待写入的字节数据


BOOL	WINAPI	CH368WriteMemDword(  // 向存储器写入一个双字
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	ULONG			iDword );  // 待写入的双字数据


BOOL	WINAPI	CH367ReadConfig(  // 从配置空间读取一个字节数据
	PVOID			iOffset,  // 指定偏移地址
	PUCHAR			oByte );  // 指向一个字节单元,用于保存读取的字节数据


BOOL	WINAPI	CH367WriteConfig(  // 向配置空间写入一个字节数据
	PVOID			iOffset,  // 指定偏移地址
	UCHAR			iByte );  // 待写入的字节数据


BOOL	WINAPI	CH368SetA15_A8(  // 设置高地址,即设置A15-A8的输出
	UCHAR			iA15_A8 );  // 位7-位0对应A15-A8的输出,1为高电平,0为低电平


BOOL	WINAPI	CH367ReadI2C(  // 从I2C接口读取一个字节数据
	UCHAR			iDevice,  // 低7位指定I2C设备地址
	UCHAR			iAddr,  // 指定数据单元的地址
	PUCHAR			oByte );  // 指向一个字节单元,用于保存读取的字节数据


BOOL	WINAPI	CH367WriteI2C(  // 向I2C接口写入一个字节数据
	UCHAR			iDevice,  // 低7位指定I2C设备地址
	UCHAR			iAddr,  // 指定数据单元的地址
	UCHAR			iByte );  // 待写入的字节数据


  HANDLE	WINAPI	CH367mOpenDevice(  // 打开CH367设备,返回句柄,出错则无效
	ULONG			iIndex,  // 指定CH367设备序号,0对应第一个设备
	BOOL			iEnableMemory,  // 是否需要支持存储器,CH367芯片不支持,CH368芯片支持
	BOOL			iEnableInterrupt,  // 是否需要支持中断
    UCHAR           iInterruptMode ); // 位0:中断输入的极性1:高电平/下降沿;0:低电平/上升沿;位1:中断输入的类型 1:边沿,0:电平

VOID	WINAPI	CH367mCloseDevice(  // 关闭CH367设备
	ULONG			iIndex );  // 指定CH367设备序号


ULONG	WINAPI	CH367mDriverCommand(  // 直接传递命令给驱动程序,出错则返回0,否则返回数据长度
	ULONG			iIndex,  // 指定CH367设备序号
	mPWIN32_COMMAND	ioCommand );  // 命令结构的指针
// 该程序在调用后返回数据长度,并且仍然返回命令结构,如果是读操作,则数据返回在命令结构中,
// 返回的数据长度在操作失败时为0,操作成功时为整个命令结构的长度,例如读一个字节,则返回mWIN32_COMMAND_HEAD+1,
// 命令结构在调用前,分别提供:命令功能代码,起始地址(可选),存取数据的长度(可选),
// 命令结构在调用后,分别返回:操作状态代码,返回的基址(可选),后续数据的长度(可选),
//   操作状态代码是由WINDOWS定义的代码,可以参考NTSTATUS.H,
//   返回的基址只适用于下列命令:获取I/O基址,获取存储器基址,获取中断号,对于其它命令则保持输入时的起始地址
//   后续数据的长度是指读操作返回的数据长度,数据存放在随后的缓冲区中,对于写操作一般为0


BOOL	WINAPI	CH367mGetIoBaseAddr(  // 获取I/O端口的基址
	ULONG			iIndex,  // 指定CH367设备序号
	mPCH367_IO_REG	*oIoBaseAddr );  // 保存I/O端口基址的单元地址


BOOL	WINAPI	CH367mSetIoBaseAddr(  // 设定I/O端口的基址
	ULONG			iIndex,  // 指定CH367设备序号
	mPCH367_IO_REG	iIoBaseAddr );  // 指定I/O端口基址


BOOL	WINAPI	CH368mGetMemBaseAddr(  // 获取存储器的基址
	ULONG			iIndex,  // 指定CH367设备序号
	mPCH368_MEM_REG	*oMemBaseAddr );  // 保存存储器基址的单元地址


BOOL	WINAPI	CH368mSetMemBaseAddr(  // 设定存储器的基址
	ULONG			iIndex,  // 指定CH367设备序号
	mPCH368_MEM_REG	iMemBaseAddr );  // 指定存储器基址,为0则关闭存储器,为-1则自动设定


BOOL	WINAPI	CH367mGetIntLine(  // 获取中断号
	ULONG			iIndex,  // 指定CH367设备序号
	PULONG			oIntLine );  // 保存中断号的单元地址


BOOL	WINAPI	CH367mSetIntLine(  // 设定中断号
	ULONG			iIndex,  // 指定CH367设备序号
	ULONG			iIntLine, // 指定中断号,为0则关闭中断,为-1则自动检测并设定
	UCHAR           iInterruptMode ); // 位0:中断输入的极性1:高电平下降沿;0:低电平上升沿;位1:中断输入的类 1:边沿,0:中断


BOOL	WINAPI	CH367mWaitInterrupt(  // 等待中断事件
	ULONG			iIndex );  // 指定CH367设备序号


BOOL	WINAPI	CH367mAbortWaitInt(  // 放弃等待中断
	ULONG			iIndex );  // 指定CH367设备序号


BOOL	WINAPI	CH367mSetIntRoutine(  // 设定中断服务程序
	ULONG			iIndex,  // 指定CH367设备序号
	mPCH367_INT_ROUTINE	iIntRoutine );  // 指定中断服务程序,为NULL则取消中断服务,否则在中断时调用该程序


BOOL	WINAPI	CH367mReadIntCommand(  // 读取中断命令缓冲区
	ULONG			iIndex,  // 指定CH367设备序号
	mPWIN32_COMMAND	oCommand,  // 指向一个足够大的缓冲区,用于保存读取的命令结构
	ULONG			iCmdIndex );  // 中断命令序号,为1或者2


BOOL	WINAPI	CH367mWriteIntCommand(  // 写入中断命令缓冲区
	ULONG			iIndex,  // 指定CH367设备序号
	mPWIN32_COMMAND	iCommand,  // 指向作为中断命令的命令结构
	ULONG			iCmdIndex );  // 中断命令序号,为1或者2


BOOL	WINAPI	CH367mReadIoByte(  // 从I/O端口读取一个字节
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	PUCHAR			oByte );  // 指向一个字节单元,用于保存读取的字节数据


BOOL	WINAPI	CH367mReadIoWord(  // 从I/O端口读取一个字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	PUSHORT			oWord );  // 指向一个字单元,用于保存读取的字数据


BOOL	WINAPI	CH367mReadIoDword(  // 从I/O端口读取一个双字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	PULONG			oDword );  // 指向一个双字单元,用于保存读取的双字数据


BOOL	WINAPI	CH367mWriteIoByte(  // 向I/O端口写入一个字节
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	UCHAR			iByte );  // 待写入的字节数据


BOOL	WINAPI	CH367mWriteIoWord(  // 向I/O端口写入一个字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	USHORT			iWord );  // 待写入的字数据


BOOL	WINAPI	CH367mWriteIoDword(  // 向I/O端口写入一个双字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定I/O端口的地址
	ULONG			iDword );  // 待写入的双字数据


BOOL	WINAPI	CH368mReadMemByte(  // 从存储器读取一个字节
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	PUCHAR			oByte );  // 指向一个字节单元,用于保存读取的字节数据


BOOL	WINAPI	CH368mReadMemDword(  // 从存储器读取一个双字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	PULONG			oDword );  // 指向一个双字单元,用于保存读取的双字数据


BOOL	WINAPI	CH368mWriteMemByte(  // 向存储器写入一个字节
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	UCHAR			iByte );  // 待写入的字节数据


BOOL	WINAPI	CH368mWriteMemDword(  // 向存储器写入一个双字
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iAddr,  // 指定存储器的地址,虚拟地址
	ULONG			iDword );  // 待写入的双字数据


BOOL	WINAPI	CH367mReadConfig(  // 从配置空间读取一个字节数据
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iOffset,  // 指定偏移地址
	PUCHAR			oByte );  // 指向一个字节单元,用于保存读取的字节数据


BOOL	WINAPI	CH367mWriteConfig(  // 向配置空间写入一个字节数据
	ULONG			iIndex,  // 指定CH367设备序号
	PVOID			iOffset,  // 指定偏移地址
	UCHAR			iByte );  // 待写入的字节数据


BOOL	WINAPI	CH368mSetA15_A8(  // 设置高地址,即设置A15-A8的输出
	ULONG			iIndex,  // 指定CH367设备序号
	UCHAR			iA15_A8 );  // 位7-位0对应A15-A8的输出,1为高电平,0为低电平


BOOL	WINAPI	CH367mReadI2C(  // 从I2C接口读取一个字节数据
	ULONG			iIndex,  // 指定CH367设备序号
	UCHAR			iDevice,  // 低7位指定I2C设备地址
	UCHAR			iAddr,  // 指定数据单元的地址
	PUCHAR			oByte );  // 指向一个字节单元,用于保存读取的字节数据


BOOL	WINAPI	CH367mWriteI2C(  // 向I2C接口写入一个字节数据
	ULONG			iIndex,  // 指定CH367设备序号
	UCHAR			iDevice,  // 低7位指定I2C设备地址
	UCHAR			iAddr,  // 指定数据单元的地址
	UCHAR			iByte );  // 待写入的字节数据


BOOL	WINAPI	CH367DelayUS(  // 延时指定微秒
	ULONG			iDelay );  // 指定要延时的微秒数,如果延时小于10则误差较大


BOOL	WINAPI	CH367mAccessBlock(  // 读取或者写入数据块
	ULONG			iIndex,  // 指定CH367设备序号
	ULONG			iAccessMode,  // 参考下面的说明
	PVOID			iAddr,  // 指定I/O端口或者存储器的地址
	PVOID			ioBuffer,  // 指向输入或者输出的缓冲区
	ULONG			iLength );  // 数据块长度,也就是读取或者写入的字节数,长度不超过32KB

// iAccessMode 定义如下
// #define		mFuncReadIoByte			0x00000010	// 读取输入输出端口,在同一个端口地址以字节为单位连续读取,最大长度32KB
// #define		mFuncReadIoWord			0x00000011	// 读取输入输出端口,在同一个端口地址以字为单位连续读取,最大长度32KB
// #define		mFuncReadIoDword		0x00000012	// 读取输入输出端口,在同一个端口地址以双字为单位连续读取,最大长度32KB
// #define		mFuncReadIoBlock		0x00000013	// 读取输入输出端口,每读取一个字节,端口地址加一,最大长度232B(从偏移地址00H读到E7H)
// #define		mFuncReadIo32Block		0x0000001f	// 读取输入输出端口,每读取一个四字节,端口地址加一/二/四,最大长度232B(从偏移地址00H读到E7H)
// #define		mFuncWriteIoByte		0x00000014	// 写入输入输出端口,在同一个端口地址以字节为单位连续写入,最大长度32KB
// #define		mFuncWriteIoWord		0x00000015	// 写入输入输出端口,在同一个端口地址以字为单位连续写入,最大长度32KB
// #define		mFuncWriteIoDword		0x00000016	// 写入输入输出端口,在同一个端口地址以双字为单位连续写入,最大长度32KB
// #define		mFuncWriteIoBlock		0x00000017	// 写入输入输出端口,每写入一个字节,端口地址加一,最大长度232B(从偏移地址00H写到E7H)
// #define		mFuncWriteIo32Block		0x00000020	// 写入输入输出端口,每写入一个四字节,端口地址加一/二/四,最大长度232B(从偏移地址00H写到E7H)
// #define		mFuncReadMemByte		0x00000018	// 读取存储器/寄存器,以字节为单位连续读,每读取一个字节,地址加一,最大长度32KB(从偏移地址0000H读到7FFFH)
// #define		mFuncReadMemDword		0x0000001a	// 读取存储器/寄存器,以双字为单位连续读,每读取一个字节,地址加四,最大长度32KB(从偏移地址0000H读到7FFFH)
// #define		mFuncWriteMemByte		0x0000001c	// 写入存储器/寄存器,以字节为单位连续写,每读取一个字节,地址加一,最大长度32KB(从偏移地址0000H写到7FFFH)
// #define		mFuncWriteMemDword		0x0000001e	// 写入存储器/寄存器,以双字为单位连续写,每读取一个双字,地址加四,最大长度32KB(从偏移地址0000H写到7FFFH)
// 其它方式不支持,上述定义在文件CH367DLL.H中


BOOL	WINAPI	CH367mSetExclusive(  // 设置独占使用当前CH367设备
	ULONG			iIndex,  // 指定CH367设备序号
	ULONG			iExclusive );  // 为0则设备可以共享使用,非0则独占使用

BOOL	WINAPI	CH367SetStream(  // 设置串口流模式
	ULONG			iIndex,      // 指定CH367设备序号
	ULONG			iMode );     // 指定模式,见下行
// 位0:     SPI时钟频率,0=31.3MHZ,1=15.6MHZ
// 位1:     SPI的I/O数/IO引脚, 0=SPI3(SCS/SCL/SDX),1=SPI4(SCS/SCL/SDX/SDI)
// 其它保留,必须为0

BOOL	WINAPI	CH367StreamSPI(  // 处理SPI数据流,3线接口,时钟线为SCL引脚,输出及输入引脚为SDX,内置上拉电阻引脚,可以外接串行FlashROM芯片25FXX的SDO/SDI引脚;片选线为SCS
							     //4线接口,输入引脚为SDI,输出引脚为SDX,时钟线为SCL引脚,片选线为SDA引脚
                                 /* SPI时序: SCL引脚为时钟输出, 默认为低电平, 在时钟上升沿之前的低电平期间输出, 引脚在时钟下降沿之前的高电平期间输入 */
                ULONG			iIndex,  // 指定CH367设备序号	
                ULONG			iWriteLength,  // 写长度,准备写出的长度
                PVOID			iWriteBuffer,  // 指向一个缓冲区,放置准备写出的数据
                PULONG			oReadLength,   // 指向长度单元,返回后为实际读取的长度
				PVOID			oReadBuffer );  // 指向一个足够大的缓冲区,用于保存读取的数据


BOOL	WINAPI	CH364mLockFlash(
		ULONG			iIndex,        // 指定CH367设备序号
		UCHAR			WRLock);	   // 锁定方式(为00H则解除写保护,为8CH则允许写保护/只读锁定,为0FFH则读写保护/完全锁定,只在复位后才能解锁)

BOOL	WINAPI	CH364mReadFlash(
		ULONG			iIndex,        // 指定CH367设备序号
		ULONG			iAddr,         // 指定FLASH的地址
		PVOID			oBuffer,	   // 指向一个缓冲区,用于保存读取的字节数据
		ULONG			iLength);       // 读取的数据长度
		
BOOL	WINAPI	CH364mEarseFlash(
		ULONG			iIndex,        // 指定CH367设备序号
		ULONG			iAddr,         // 指定FLASH的地址
		ULONG			iLength );	   // 指定擦除的长度，每4096字节即4K为一个扇区,最小擦除单位是扇区

BOOL	WINAPI	CH364mWriteFlash(
		ULONG			iIndex,        // 指定CH367设备序号
		ULONG			iAddr,         // 指定I/O端口的地址,该地址可以为IO偏移地址(<=0xE7)和绝对IO地址
		PVOID			iBuffer,	   // 指向一个字节单元,用于保存读取的字节数据
		ULONG			iLength);  

#ifdef __cplusplus
}
#endif

#endif		// _CH367_DLL_H
