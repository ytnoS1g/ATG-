#ifndef LWCOMSTREAMER_H
#define LWCOMSTREAMER_H


class LwComStreamer{
public:
   // LwComStreamer(){}
   // LwComStreamer(){}
    virtual void open() = 0;
    virtual void close() = 0;
    virtual bool read(QByteArray &ba, uint32_t size) = 0;
    virtual bool write(const QByteArray &ba) = 0;
};


#endif // LWCOMSTREAMER_H
