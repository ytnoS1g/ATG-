#ifndef LWCOMSERIALSTREAMER_H
#define LWCOMSERIALSTREAMER_H
#include "lwcomstreamer.h"
#include <QSerialPort>
class LwComSerialStreamer: public LwComStreamer
{
private:
    QSerialPort *_serial;
    int _timeout;
public:
    LwComSerialStreamer();
    ~LwComSerialStreamer();
    bool open(QString serialPort, qint32 baudRate);
    void close();
    bool read(QByteArray &ba, uint32_t size);
    bool write(const QByteArray &ba);
    int getTimeout();
    void setTimeout(int);
};
#endif // LWCOMSERIALSTREAMER_H
