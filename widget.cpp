#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>





Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    arduinoIsAvailable = false;
    arduinoPortName = "";
    arduino = new QSerialPort();

    // qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    // foreach(const QSerialPortInfo &  serialPortInfo, QSerialPortInfo::availablePorts()){
    //     qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
    //     if(serialPortInfo.hasVendorIdentifier()){
    //         qDebug()<< "Vendor ID: "<< serialPortInfo.vendorIdentifier();
    //     }
    //     qDebug() << "Has product ID: " << serialPortInfo.hasProductIdentifier();
    //     if(serialPortInfo.hasProductIdentifier()){
    //         qDebug()<< "Vendor ID: "<< serialPortInfo.productIdentifier();
    //     }
    // }

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() &&serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduinoUnoVendorID){
                if(serialPortInfo.productIdentifier() == arduinoUnoProductID){
                    arduinoPortName = serialPortInfo.portName();
                    arduinoIsAvailable = true;
                }
            }
        }
    }
    if(arduinoIsAvailable){
        //open and configure port
        arduino->setPortName(arduinoPortName);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }
    else
    {
        //Give error message
        QMessageBox::warning(this,"Port Error", "Arduino not found!");
    }
}

Widget::~Widget()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}



void Widget::on_onButton_clicked()
{
    Widget::update_lights(QString::number(1));
}


void Widget::on_offButton_clicked()
{
       Widget::update_lights(QString::number(2));
}
void Widget::update_lights(QString command){
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    }
    else{
        qDebug()<< "Can't write to serial";
        if(arduino->isOpen()){
            qDebug()<< "is open";
        }
    }
}

