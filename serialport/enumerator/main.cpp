

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QtSerialPort/QSerialPortInfo>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//starts app

    QVBoxLayout *layout = new QVBoxLayout;//begins layout

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {//for all ports connected
        QString s = QObject::tr("Port: ") + info.portName() + "\n"
                    + QObject::tr("Location: ") + info.systemLocation() + "\n"
                    + QObject::tr("Description: ") + info.description() + "\n"
                    + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
                    + QObject::tr("Serial number: ") + info.serialNumber() + "\n"
                    + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
                    + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
                    + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";

        QLabel *label = new QLabel(s);//app label
        layout->addWidget(label);
    }

    QWidget *workPage = new QWidget;
    workPage->setLayout(layout);//ends layout

    QScrollArea area;
    area.setWindowTitle(QObject::tr("Info about all available serial ports."));
    area.setWidget(workPage);
    area.show();//window parameters

    return a.exec();
}
