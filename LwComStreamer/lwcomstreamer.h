#ifndef LWCOMSTREAMER_H
#define LWCOMSTREAMER_H
#include <QByteArray>


class LwComStreamer{
public:
    LwComStreamer(){}
   ~LwComStreamer(){}
    virtual void close() = 0;
    virtual bool read(QByteArray &ba, uint32_t size) = 0;
    virtual bool write(const QByteArray &ba) = 0;
};


#endif // LWCOMSTREAMER_H
