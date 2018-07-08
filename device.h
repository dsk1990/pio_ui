#ifndef DEVICE_H
#define DEVICE_H

class Device {
public:
    virtual bool open();
    virtual bool close();
    virtual bool isOpen();
    virtual bool getHandle();

////抽象类是否带有成员变量？
/// 具体device 实现可能已有isopen的接口
//private:
//    bool openFlag;
}

#endif // DEVICE_H
