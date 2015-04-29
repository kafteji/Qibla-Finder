/**
  ******************************************************************************
  * @file    mainwindow.h
  * @author  Fahmi Ghediri
  * @version V1.0
  * @date    20-April-2015
  * @brief   Contains structure, class and constants declaration,   
  ******************************************************************************
**/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>



#define MAX_SIZE 25

// for start and end fields in BT_Packet

#define START (quint8) 0x65

#define END (quint8) 0x66

// for id field in BT_Packet

#define COMMAND (quint8) 0x67

#define DATA (quint8) 0x68

// define the length field content

#define LENGTH (quint8) 0x25


// origin and Mekka coordinates

#define GROUND_ZERO_LONGITUDE (double) 0.0

#define GROUND_ZERO_LATITUDE (double) 0.0

#define MEKKA_LATITUDE       (double) 21.4224812

#define MEKKA_LONGITUDE      (double) 39.8261978



struct BT_Packet
{
        quint8 start ;
        quint8 id;
        quint8 length;
        quint8 data[MAX_SIZE-4];
        quint8 end ;

};
typedef struct BT_Packet BT_Packet;





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    qint8 calculate_direction();


private slots:
    void on_actionClose_triggered();

    void on_actionHelp_triggered();

    void on_connect_clicked();

    void on_detect_clicked();

    void on_disconnect_clicked();

    void isDataReady();

private:
    Ui::MainWindow *mainUi;
    QSerialPort* serialPort ;
    QByteArray receivedData,toSend ;
    double longitude, latitude ;
    char northSouth, eastWest;
    bool isReceived;
    BT_Packet packet;


    void parseData();

};

#endif // MAINWINDOW_H
