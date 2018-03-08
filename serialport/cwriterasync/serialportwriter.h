
#ifndef SERIALPORTWRITER_H
#define SERIALPORTWRITER_H

#include <QtSerialPort/QSerialPort>

#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QObject>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class SerialPortWriter : public QObject
{
    Q_OBJECT

public:
    SerialPortWriter(QSerialPort *serialPort, QObject *parent = 0);
    ~SerialPortWriter();

    void write(const QByteArray &writeData);

private slots:
    void handleBytesWritten(qint64 bytes);
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort     *m_serialPort;
    QByteArray      m_writeData;
    QTextStream     m_standardOutput;
    qint64          m_bytesWritten;
    QTimer          m_timer;
};

#endif
