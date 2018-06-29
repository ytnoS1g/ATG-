#include <QSerialPort>
#include <qserialport.h>
#include <lwcomserialstreamer.h>
#include <QTimer>
#include <QDateTime>

LwComSerialStreamer::LwComSerialStreamer()
{
    _serial = new QSerialPort;
}
LwComSerialStreamer::~LwComSerialStreamer()
{
    delete _serial;
}

bool LwComSerialStreamer::open(QString serialPort,qint32 baudRate)
{
    close();

    _serial->setPortName(serialPort);
    _serial->setDataTerminalReady(true);
    _serial->setBaudRate(baudRate);
    _serial->setReadBufferSize(0);
    _serial->setDataBits(QSerialPort::Data8);
    _serial->setParity(QSerialPort::NoParity);
    _serial->setStopBits(QSerialPort::OneStop);
    _serial->setFlowControl(QSerialPort::NoFlowControl);
    /* i believe DTR & DTxxx signals shall be enabled as well. IRDA needs additional power, which delivered by DTR,DTxx signals */

    if (_serial->QSerialPort::open(QIODevice::ReadWrite))
        return true;
    else
        return false;
}
void LwComSerialStreamer::close()
{
    if(_serial->isOpen())
        _serial->QSerialPort::close();
}
bool LwComSerialStreamer::read(QByteArray &ba, uint32_t size)
{
    if(_serial->isReadable())
    {
        QTime to = QTime::currentTime();

        to.start();

        ba.resize(size);

        qint64 bytes =  _serial->read(ba.data(),size);

        ba.resize(bytes);

        while(to.elapsed() < _timeout && bytes < size)//full timeout or all bytes
        {
            int ms = _timeout - to.elapsed();//TODO check if negative/0

            bool moreBytes = _serial->waitForReadyRead(ms);
            if(moreBytes)
            {
                QByteArray tmp;
                tmp.resize(size);

                bytes = _serial->read(tmp.data(),size);
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

bool LwComSerialStreamer::write(const QByteArray &ba)
{
    if(_serial->isWritable())
    {
        int bytes =_serial->write(ba);
        if(bytes > 0)//any bytes were read
            return true;
        else
            return false;
    }
    else
        return false;
}
int LwComSerialStreamer::getTimeout()
{
    return _timeout;
}

void LwComSerialStreamer::setTimeout(int time)
{
    if(time > 0)
        _timeout = time;
}

