

#include <QtSerialPort/QSerialPort>

#include <QTextStream>
#include <QCoreApplication>
#include <QFile>
#include <QStringList>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication coreApplication(argc, argv);
    int argumentCount = QCoreApplication::arguments().size();
    QStringList argumentList = QCoreApplication::arguments();

    QTextStream standardOutput(stdout);

    if (argumentCount == 1) {
        standardOutput << QObject::tr("Usage: %1 <serialportname> [baudrate]").arg(argumentList.first()) << endl;
        return 1;
    }

    QSerialPort serialPort;
    QString serialPortName = argumentList.at(1);
    serialPort.setPortName(serialPortName);

    int serialPortBaudRate = (argumentCount > 2) ? argumentList.at(2).toInt() : QSerialPort::Baud9600;
    serialPort.setBaudRate(serialPortBaudRate);

    if (!serialPort.open(QIODevice::WriteOnly)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;
        return 1;
    }

    QFile dataFile;
    if (!dataFile.open(stdin, QIODevice::ReadOnly)) {
        standardOutput << QObject::tr("Failed to open stdin for reading") << endl;
        return 1;
    }

    QByteArray writeData(dataFile.readAll());
    dataFile.close();

    if (writeData.isEmpty()) {
        standardOutput << QObject::tr("Either no data was currently available on the standard input for reading, or an error occurred for port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;
        return 1;
    }

    qint64 bytesWritten = serialPort.write(writeData);

    if (bytesWritten == -1) {
        standardOutput << QObject::tr("Failed to write the data to port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;
        return 1;
    } else if (bytesWritten != writeData.size()) {
        standardOutput << QObject::tr("Failed to write all the data to port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;
        return 1;
    } else if (!serialPort.waitForBytesWritten(5000)) {
        standardOutput << QObject::tr("Operation timed out or an error occurred for port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;
        return 1;
    }

    standardOutput << QObject::tr("Data successfully sent to port %1").arg(serialPortName) << endl;

    return 0;
}
