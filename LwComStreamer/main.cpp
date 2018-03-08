#include "lwcomstreamer.h"
#include "lwcomserialstreamer.h"
#include "lwcomtcpstreamer.h"
#include <QCoreApplication>
#include <QSerialPort>

int main(int argc, char **argv) {
    QCoreApplication *app;

    /* Serial: 57600 baudrate */
    /* Tcp: IP : 4001 */
    /* To test the connection, you can type P and LiveWire shall reply with I */

    LwComTcpStreamer * tcp = new LwComTcpStreamer();
    LwComSerialStreamer * serial = new LwComSerialStreamer();
    QString serialPort = "COM1";
    qint32 baudRate = 57600;
    if(serial->open(serialPort,baudRate))
    {
        qDebug("Success");
    }
    serial->close();
    app->exec();
    return 0;
}
