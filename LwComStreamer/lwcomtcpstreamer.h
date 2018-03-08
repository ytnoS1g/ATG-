#ifndef LWCOMTCPSTREAMER_H
#define LWCOMTCPSTREAMER_H
#include "lwcomstreamer.h"
#include <QTcpSocket>
class LwComTcpStreamer : public LwComStreamer
{
private:
    QTcpSocket *_socket;
    int _timeout;
public:
    LwComTcpStreamer();
    ~LwComTcpStreamer();
    bool open(QHostAddress host, uint16_t port);
    void close();
    bool read(QByteArray &ba, uint32_t size);
    bool write(const QByteArray &ba);
    int getTimeout();
    void setTimeout(int);
};

#endif // LWCOMTCPSTREAMER_H
