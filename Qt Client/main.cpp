/**
  ******************************************************************************
  * @file    main.cpp 
  * @author  Fahmi Ghediri
  * @version V1.0
  * @date    23-April-2015
  * @brief   the main function for the Qibla Finder client        
  ******************************************************************************
**/



#include "mainwindow.h"
#include <QApplication>
#include "QDebug"
#include "QMainWindow"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
