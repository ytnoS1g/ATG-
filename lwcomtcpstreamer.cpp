#include "lwcomtcpstreamer.h"
#include <QHostAddress>
#include <QTcpSocket>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDateTime>
#define VERIFY( V, R )  if ( !(V) ){ retVal = (R); break; }
LwComTcpStreamer::LwComTcpStreamer()
{
    _socket = new QTcpSocket();
}

LwComTcpStreamer::~LwComTcpStreamer()
{
    delete _socket;
}

bool LwComTcpStreamer::open(QHostAddress host, uint16_t port)
{
    close();

    _socket->connectToHost(host,port);

    if(_socket->waitForConnected(_timeout))
        return true;
    else
        return false;
}
void LwComTcpStreamer::close()
{
    if (_socket->isOpen())
        _socket->disconnectFromHost();
}

bool LwComTcpStreamer::read(QByteArray &ba, uint32_t size)
{
    if(_socket->isReadable() && _socket->bytesAvailable() > size)
    {
        QTime to = QTime::currentTime();

        to.start();

        ba.resize(size);

        qint64 bytes =  _socket->read(ba.data(),size);

        ba.resize(bytes);

        while(to.elapsed() < _timeout && bytes < size)//full timeout or all bytes
        {
            int ms = _timeout - to.elapsed();//TODO check if negative/0

            bool moreBytes = _socket->waitForReadyRead(ms);//wait for more
            if(moreBytes)
            {
                QByteArray tmp;
                tmp.resize(size);

                bytes =  _socket->read(tmp.data(),size);
                tmp.resize(bytes);
                ba.append(tmp);
            }
            else
                break;
        }
        if(static_cast<uint32_t>(bytes) == size)
            return true;
        else if(bytes == -1)
            return false;//TODO error handling
        else
            return false;
    }
    else
        return false;
}

bool LwComTcpStreamer::write(const QByteArray &ba)
{
    if(_socket->isWritable())
    {
        int bytes =_socket->write(ba);
        if(bytes > 0)//any bytes were read
            return true;
        else
            return false;
    }
    else
        return false;
}

int LwComTcpStreamer::getTimeout()
{
    return _timeout;
}

void LwComTcpStreamer::setTimeout(int time)
{
    if(time > 0)
        _timeout = time;
}
