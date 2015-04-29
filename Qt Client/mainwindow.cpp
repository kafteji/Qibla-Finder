/**
  ******************************************************************************
  * @file    mainwindow.cpp 
  * @author  Fahmi Ghediri
  * @version V1.0
  * @date    23-April-2015
  * @brief   contains methods which receives, parses data and calculates 
  *	     the Qibla direction      
  ******************************************************************************
**/


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QtCore/qmath.h>
#include <QDebug>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainUi(new Ui::MainWindow)
{
    mainUi->setupUi(this);
    QPixmap bkgnd(":/rc/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    foreach (const QSerialPortInfo info, QSerialPortInfo::availablePorts()) {
        mainUi->comboBox->addItem(info.portName()+" ("+info.description()+") ");
    }

    this->serialPort = new QSerialPort(this);
    this->isReceived=false;
    this->mainUi->disconnect->setDisabled(true);

    connect(this->serialPort,SIGNAL(readyRead()),this,SLOT(isDataReady()));

}

MainWindow::~MainWindow()
{
    if(this->serialPort->isOpen()){
        this->serialPort->close();
    }
    delete mainUi;

}

void MainWindow::on_actionClose_triggered()
{
    if(this->serialPort->isOpen()){
        this->serialPort->close();
    }
    this->close();
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox::information(this,"About Qibla Finder","Designed and Implemented By Fahmi Ghediri \n\n 1/ Connect to the COM port \n\n 2/ wait for data from the STM32 \n\n 3/ Click 'Detect Qibla' and you will see a blinking LED indicating the Qibla\n Direction \n\n Greets !! :)");
}




void MainWindow::on_connect_clicked()
{
    QString name = mainUi->comboBox->currentText().left(4);

    this->serialPort->setPortName(name);
    this->serialPort->setBaudRate(QSerialPort::Baud9600);
    this->serialPort->setFlowControl(QSerialPort::NoFlowControl);
    this->serialPort->setParity(QSerialPort::NoParity);
    this->serialPort->setStopBits(QSerialPort::OneStop);


    if(!this->serialPort->open(QIODevice::ReadWrite)){
        QMessageBox::critical(this,"Fatal Error","Cannot open port : "+name);
    }
    else{
        QMessageBox::information(this,"Success","Succesfully connected to port :"+name +
                                 "\n\n Waiting Data from the STM32 Micro-controller");
        this->mainUi->connect->setDisabled(true);
        this->mainUi->disconnect->setDisabled(false);
    }

}

void MainWindow::on_detect_clicked()
{
    if(!this->serialPort->isOpen()){
        QMessageBox::warning(this,"Warning !!","You must connect to the valid COM port before proceeding. \n Please Try again !!");
    }else if(!this->isReceived){
        QMessageBox::warning(this,"Warning !!","Please wait for data to be received");
    }else{
        packet.start=START;
        packet.id=COMMAND;
        packet.length=LENGTH;
        for (int i = 0; i < 21; ++i) {
            packet.data[i]= 0x30;
        }
        packet.data[0]=this->calculate_direction();
        packet.end=END;
    }
    QByteArray buffer;
    buffer.append(packet.start);
    buffer.append(packet.id);
    buffer.append(packet.length);
    for (int i = 0; i < 21; ++i) {
        buffer.append(packet.data[i]);
    }
    buffer.append(packet.end);

    this->serialPort->write(buffer);
    this->receivedData.clear();


}


qint8 MainWindow::calculate_direction(){
    qint8 ledNum =0x00;
    double PI= acos(-1);
    double angle = atan((this->latitude-MEKKA_LATITUDE)/(this->longitude-MEKKA_LONGITUDE));

    if(this->longitude > MEKKA_LONGITUDE){

        if(angle >= (3*PI/8) ) return 0x65;

        if((angle < (3*PI/8)) && (angle >= PI/8)) return 0x66;

        if(angle < (PI/8) && (angle >= (-PI/8)) ) return 0x67;

        if((angle < (-PI/8)) && (angle >= (3*PI/8))) return 0x68;

        if(angle < (3*PI/8) )return 0x61;

    } else{

        if(angle >= (3*PI/8) ) return 0x61;

        if((angle < (3*PI/8)) && (angle >= PI/8)) return 0x62;

        if(angle < (PI/8) && (angle >= (-PI/8)) ) return 0x63;

        if((angle < (-PI/8)) && (angle >= (3*PI/8))) return 0x64;

        if(angle < (3*PI/8) )return 0x65;
    }

    return ledNum;
}


void MainWindow::on_disconnect_clicked()
{
    if(this->serialPort->isOpen()){
        this->serialPort->close();
        QMessageBox::information(this,"Disconnected","Succesfully disconnected from Serial Port "+
                                 this->serialPort->portName()  +" !!");
        this->mainUi->connect->setDisabled(false);
        this->mainUi->disconnect->setDisabled(true);
    } else {
        QMessageBox::critical(this,"Error","Already disconnected from the Serial Port !!");
    }
}


void MainWindow::isDataReady(){
    QByteArray aux = this->serialPort->readAll();
    this->receivedData.append(aux);
    if(receivedData.endsWith('f')){
        this->isReceived=true;
    }
    if(this->isReceived){

        QMessageBox::information(this,"Data Received","Data received successfully from the Microcontroller !!");
        this->parseData();
    }

}


void MainWindow::parseData(){
    QString lati, longi;
    if((receivedData.at(0) == START) && (receivedData.at(1) == DATA) && (receivedData.at(2) == LENGTH) &&
            (receivedData.at(MAX_SIZE-1) == END )){
        for (int i = 3; i < 12 ; ++i) {
            lati.append(receivedData.at(i));
        }
        this->northSouth=receivedData.at(12);

        for (int i = 13; i < 23; ++i) {
            longi.append(receivedData.at(i));
        }

        this->eastWest=receivedData.at(23);

        this->latitude = lati.left(2).toDouble()+(lati.right(7).toDouble()/60);
        this->longitude = longi.left(3).toDouble()+(longi.right(7).toDouble()/60);

        if(eastWest == 'W'){
            longitude *= -1;
        }
        if(northSouth == 'S'){
            latitude*= -1;
        }

        this->mainUi->latitude->setText(QString("%1").arg(latitude, 0, 'g', 8));
        this->mainUi->longitude->setText(QString("%1").arg(longitude, 0, 'g', 8));

    } else{
        QMessageBox::critical(this,"Error"," The received data is corrupted please try again !!");

    }
}
