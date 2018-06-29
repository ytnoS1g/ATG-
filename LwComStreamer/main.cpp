#include "lwcomstreamer.h"
#include "lwcomserialstreamer.h"
#include "lwcomtcpstreamer.h"
#include <QCoreApplication>
#include <QSerialPort>
#include <QHostAddress>

int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);

    /* Serial: 57600 baudrate */
    /* Tcp: IP : 4001 */
    /* To test the connection, you can type P and LiveWire shall reply with I */
    LwComStreamer _streamer;
    LwCom(_streamer);
    LwComTcpStreamer * tcp = new LwComTcpStreamer();
    LwComSerialStreamer * serial = new LwComSerialStreamer();

    QString serialPort = "COM1";
    qint32 baudRate = 57600;

    QHostAddress ip;
    ip.setAddress("192.168.0.110");
    uint16_t port = 4001;

    if(tcp->open(ip,port))
    {
        qDebug("Success");
    }

    tcp->close();

    return a.exec();
}
