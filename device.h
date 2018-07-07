#ifndef DEVICE_H
#define DEVICE_H

class Device {
public:
    virtual bool open();
    virtual bool close();
    virtual bool isOpen();

private:
    bool openFlag;
}

#endif // DEVICE_H
